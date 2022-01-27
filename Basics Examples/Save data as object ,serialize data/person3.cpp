#include<QFile>
#include <QApplication>
#include<QDataStream>
#include<QFile>
#include <QMetaType>
#include<QBuffer>
#include<QDebug>
#include<QJsonObject>
#include<QJsonArray>

class Person3
{
public:
    QString name;
    QString number;
    qint8 age;

    Person3(QString name,QString number,qint8 age)
    {
        this->name=name;
        this->number=number;
        this->age = age;
    }
    Person3(){}

    void showData()
    {
        qDebug()<<name<<" "<<number<<" "<<age;
    }


    void fromJson( const QJsonObject & json)
    {
        name = json["name"].toString();
        number = json["number"].toString();
        age = json["age"].toInt();
    }

    QJsonObject  toJson()
    {
        QJsonObject json;
        json["name"] = name;
        json["number"] = number;
        json["age"] = age;
        return  json;
    }

};

void saveData3(const QList<QJsonObject> &data, const QString &filename="C:/Users/Nishant Choudhary/Desktop/temp.bin")
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly )) return;

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_4_0);

    // Magic number
    ds << (quint32)0xDEADBEEF;
    // Version
    ds << (qint32)1;

    // or json array
    QJsonArray temp;
    foreach(QJsonObject r, data)
        temp.append(r);
    ds<<temp;
    file.close();

}

QJsonArray readData3(const QString &filename="C:/Users/Nishant Choudhary/Desktop/temp.bin")
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_4_0);

    // Magic number
    quint32 magic;
    ds >> magic;
    if (magic != 0xDEADBEEF) {
        qWarning("Wrong magic!\n");
        return QJsonArray();
    }
    // Version
    qint32 version;
    ds >> version;
    if (version != 1) {
        qWarning("Wrong version!\n");
        return  QJsonArray();
    }

    QJsonArray recordList;
    ds >> recordList;
    file.close();
    return recordList;

}

void PersonExample3()
{
    Person3 person1("ramesh","7742247438",20);
    Person3 person2("suraj","7845157825",19);
    Person3 person3("ankita","9945157825",18);
    Person3 person4("kajal","7795157825",17);
    QList<QJsonObject> data;
    data<<person1.toJson()<<person3.toJson()<<person3.toJson()<<person4.toJson();
    saveData3(data);

    Person3 person11;
    Person3 person32;
    Person3 person33;
    Person3 person44;
    QList<Person3 >person3list;
    person3list<<person11<<person32<<person33<<person44;
    QJsonArray data1;
    data1 = readData3();
    for(int i=0;i<4;i++)
    {
        person3list[i].fromJson(data1.at(i).toObject());
        person3list[i].showData();
    }
}
