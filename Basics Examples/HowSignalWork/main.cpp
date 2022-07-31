#include <QCoreApplication>
#include "A.h"
#include "B.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
     A a;
     B b;
     QObject::connect(&a,&A::startexe,[=]()
     {
         for(int i=0;i<100;i++)
             qDebug()<<"this is lamba function";
     });
     QObject::connect(&a,&A::startexe,&b,&B::print);
     a.print();
    return app.exec();
}



