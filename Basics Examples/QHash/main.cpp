#include <QCoreApplication>
#include<QHash>
#include<QDebug>
int main(int argc, char *argv[])
{
    // same as a map interface but different implementation
    // time complexity of serach is O(1) in QHash and n(Logn) in QMap

    QCoreApplication a(argc, argv);
   QHash<QString,int>employee;
   for(int i=0;i<5;i++)
   {
       employee.insert(QString::number(i)+"name",i);
   }

   for(auto it:employee)
   {
       qDebug()<<employee.key(it);
   }
   QHashIterator<QString,int> mapit(employee);
   while(mapit.hasNext())
   {
       auto temp= mapit.next();
       qDebug()<<temp.key()<<" "<<temp.value();
   }
    return a.exec();
}
