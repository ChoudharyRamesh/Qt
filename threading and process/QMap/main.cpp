#include <QCoreApplication>
#include<QMap>
#include<QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
   QMap<QString,int>employee;
   for(int i=0;i<5;i++)
   {
       employee.insert(QString::number(i)+"name",i);
   }

   for(auto it:employee)
   {
       qDebug()<<employee.key(it);
   }
   QMapIterator<QString,int> mapit(employee);
   while(mapit.hasNext())
   {
       auto temp= mapit.next();
       qDebug()<<temp.key()<<" "<<temp.value();
   }
    return a.exec();
}
