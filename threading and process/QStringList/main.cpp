#include <QCoreApplication>
#include<QStringList>
#include<QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList stringlist;
    stringlist<<"okk"<<"hello"<<"world";
    QString string = "a,b,c,d,e,f,g,h";
    stringlist.append(string.split(','));
    qDebug()<<stringlist;
    return a.exec();
}
