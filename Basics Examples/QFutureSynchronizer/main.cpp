#include <QCoreApplication>
#include<QtConcurrent>
#include<QFutureSynchronizer>
#include<QDebug>

int  function1()
{
    int num=0;
    for(int i=0;i<1000000000;i++)
         num++;
    return  num;
}

int  function2()
{
    int num=0;
    for(int i=0;i<100000000;i++)
         num++;
    return  num;
}
int  function3()
{
    int num=0;
    for(int i=0;i<10000000;i++)
         num++;
    return  num;
}
int  function4()
{
    int num=0;
    for(int i=0;i<1000000;i++)
         num++;
    return  num;
}
int  function5()
{
    int num=0;
    for(int i=0;i<100000;i++)
         num++;
    return  num;
}
int  function6()
{
    int num=0;
    for(int i=0;i<10000;i++)
         num++;
    return  num;
}

int  function7()
{
    int num=0;
    for(int i=0;i<1000;i++)
         num++;
    return  num;
}
int  function8()
{
    int num=0;
    for(int i=0;i<100;i++)
         num++;
    return  num;
}
int  function9()
{
    int num=0;
    for(int i=0;i<10;i++)
         num++;
    return  num;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFutureSynchronizer<int> synchronizer;
    synchronizer.addFuture(QtConcurrent::run(function1));
    synchronizer.addFuture(QtConcurrent::run(function2));
    synchronizer.addFuture(QtConcurrent::run(function3));
    synchronizer.addFuture(QtConcurrent::run(function4));
    synchronizer.addFuture(QtConcurrent::run(function5));
    synchronizer.addFuture(QtConcurrent::run(function6));
    synchronizer.addFuture(QtConcurrent::run(function7));
    synchronizer.addFuture(QtConcurrent::run(function8));
    synchronizer.addFuture(QtConcurrent::run(function9));
     // synchronizer will automatically watis for all process to done.
    qint64 final_result=0;
    for(auto future:synchronizer.futures())
    {
        final_result+=future.result();
    }
    qDebug()<<final_result+1;
    return a.exec();
}
