#include<QFile>
#include <QApplication>
#include<QDataStream>
#include<QFile>
#include <QMetaType>
#include<QBuffer>
#include<QDebug>
#include<QJsonObject>
#include<QJsonArray>

class  Person
{

public:
    QString name;
    QString number;
    qint8 age;
    ~Person(){}
    Person(){}
    Person ( const QString & name ,const  QString & number , const qint8 & age)
    {
        this->name=name;
        this->number=number;
        this->age = age;
    }

    void showdata()
    {
        qDebug()<<name<<" "<<number<<" "<<age;
    }

};

QDataStream& operator<<(QDataStream &s, const Person &r)
{
    s <<r.name<<r.number<<r.age;
    // or encoded
    //  s <<QVariant(r.name).toByteArray().toHex() <<QVariant(r.number).toByteArray().toHex() <<QVariant(r.age).toByteArray().toHex();
    return s;
}

QDataStream& operator >>(QDataStream &s, Person &r)
{
    QString temp;
    s>>temp;
    r.name=temp;
    s>>temp;
    r.number= temp;
    qint8 itemp;
    s>>itemp;
    r.age=itemp;
    return s;
    // or decode
    //   QByteArray temp;
    //    s>>temp;
    //    r.name=QByteArray::fromHex(temp);
    //    s>>temp;
    //    r.number= QByteArray::fromHex(temp);
    //    s>>temp;
    //    r.age=QByteArray::fromHex(temp).toInt();
    //    return s;
}

void saveData(const QList<Person> &data, const QString &filename="C:/Users/Nishant Choudhary/Desktop/temp.bin") {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly )) return;

    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_4_0);

    // Magic number
    ds << (quint32)0xDEADBEEF;
    // Version
    ds << (qint32)1;

    foreach(Person r, data)
        ds <<r;
    file.close();
}

QList<Person> readData(const QString &filename="C:/Users/Nishant Choudhary/Desktop/temp.bin") {
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QDataStream ds(&file);
    ds.setVersion(QDataStream::Qt_4_0);

    // Magic number
    quint32 magic;
    ds >> magic;
    if (magic != 0xDEADBEEF) {
        qWarning("Wrong magic!\n");
        return QList<Person>();
    }
    // Version
    qint32 version;
    ds >> version;
    if (version != 1) {
        qWarning("Wrong version!\n");
        return QList<Person>();
    }


    QList<Person> recordList;
    Person person;
    while (!ds.atEnd()) {
        ds >> person;
        recordList.append(person);
    }
    file.close();
    return recordList;

}

void PersonExample()
{
    Person person1("ramesh","7742247438",20);
    Person person2("suraj","7845157825",19);
    Person person3("ankita","9945157825",18);
    Person person4("kajal","7795157825",17);
    QList<Person> data;
    data<<person1<<person2<<person3<<person4;
    saveData(data);

    Person person11;
    Person person22;
    Person person33;
    Person person44;
    QList<Person> data1;
    data1 = readData();

    foreach(Person temp ,data1)
    {
        temp.showdata();
    }
}
