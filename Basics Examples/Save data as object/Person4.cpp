#include<QFile>
#include <QApplication>
#include<QDataStream>
#include<QFile>
#include <QMetaType>
#include<QBuffer>
#include<QDebug>
#include<QJsonObject>
#include<QJsonArray>
#include<QBitArray>
#include<QJsonDocument>
//#define s(x) QByteArray::fromHex(x)

class Person4
{
public:
    QString name;
    QString number;
    qint8 age;

    Person4(QString name,QString number,qint8 age)
    {
        this->name=name;
        this->number=number;
        this->age = age;
    }
    Person4(){}

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

void saveData4(const QList<QJsonObject> &data, const QString &filename="C:/Users/Nishant Choudhary/Desktop/temp.bin")
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly )) return;

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_4_0);

    // Magic number
    ds << (quint32)0xDEADBEEF;
    // Version
    ds << (qint32)1;


    QJsonArray temp;
    foreach(QJsonObject r, data)
        temp.append(r);
    ds<< QJsonDocument(temp).toBinaryData().toHex().toPercentEncoding();
    file.close();

   qDebug()<< QJsonDocument(temp).toBinaryData().toHex();
}

QJsonArray readData4(const QString &filename="C:/Users/Nishant Choudhary/Desktop/temp.bin")
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


    QByteArray bytearray;
    ds>>bytearray;
    QByteArray bytearray2 = QByteArray::fromPercentEncoding(QByteArray::fromHex(bytearray));
   return QVariant(QJsonDocument::fromBinaryData(bytearray2).toVariant()).toJsonArray();
    file.close();


}

void PersonExample4()
{
    Person4 person1("ramesh","7742247438",20);
    Person4 person2("suraj","7845157825",19);
    Person4 person3("ankita","9945157825",18);
    Person4 person4("kajal","7795157825",17);
    QList<QJsonObject> data;
    data<<person1.toJson()<<person2.toJson()<<person3.toJson()<<person4.toJson();
    saveData4(data);

    Person4 person11;
    Person4 person32;
    Person4 person33;
    Person4 person44;
    QList<Person4 >person3list;
    person3list<<person11<<person32<<person33<<person44;
    QJsonArray data1;
    data1 = readData4();
    for(int i=0;i<4;i++)
    {
        person3list[i].fromJson(data1.at(i).toObject());
        person3list[i].showData();
    }
}

