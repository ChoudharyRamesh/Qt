#include<QFile>
#include <QApplication>
#include<QDataStream>
#include<QFile>
#include <QMetaType>
#include<QBuffer>
#include<QDebug>
#include<QJsonObject>
#include<QJsonArray>

class Person2
{
public:
    QString name;
    QString number;
    qint8 age;

    Person2(QString name,QString number,qint8 age)
    {
        this->name=name;
        this->number=number;
        this->age = age;
    }
    Person2(){}

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

void saveData2(const QList<QJsonObject> &data, const QString &filename="C:/Users/Nishant Choudhary/Desktop/temp.bin") {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly )) return;

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_4_0);

    // Magic number
    ds << (quint32)0xDEADBEEF;
    // Version
    ds << (qint32)1;

    foreach(QJsonObject r, data)
        ds<<r;
    file.close();

}

QList<QJsonObject> readData2(const QString &filename="C:/Users/Nishant Choudhary/Desktop/temp.bin") {
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_4_0);

    // Magic number
    quint32 magic;
    ds >> magic;
    if (magic != 0xDEADBEEF) {
        qWarning("Wrong magic!\n");
        return  QList<QJsonObject>();
    }
    // Version
    qint32 version;
    ds >> version;
    if (version != 1) {
        qWarning("Wrong version!\n");
        return  QList<QJsonObject>();
    }


    QList<QJsonObject> recordList;
    QJsonObject json;
    while (!ds.atEnd()) {
        ds >> json;
        recordList.append(json);
    }
    file.close();
    return recordList;



}

void PersonExample2()
{
    Person2 person1("ramesh","7742247438",20);
    Person2 person2("suraj","7845157825",19);
    Person2 person3("ankita","9945157825",18);
    Person2 person4("kajal","7795157825",17);
    QList<QJsonObject> data;
    data<<person1.toJson()<<person2.toJson()<<person3.toJson()<<person4.toJson();
    saveData2(data);

    Person2 person11;
    Person2 person22;
    Person2 person33;
    Person2 person44;
    QList<Person2 >person2list;
    person2list<<person11<<person22<<person33<<person44;
    QList<QJsonObject> data1;
    data1 = readData2();
    for(int i=0;i<4;i++)
    {
        person2list[i].fromJson(data1[i]);
        person2list[i].showData();
    }

}
