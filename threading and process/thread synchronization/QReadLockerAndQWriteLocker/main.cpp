#include <QCoreApplication>
#include<QFile>
#include<QDataStream>
#include<QDebug>
#include<QThread>
#include<QReadWriteLock>
#include<QReadLocker>
#include<QWriteLocker>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int sharedVariable=0;
    QReadWriteLock readwritelocker;

    QThread * thread1 = QThread::create([&]()
    {
        for(int i=0;i<50000000;i++)
        {
            if(i%1000000==0)
            {
                QWriteLocker lock(&readwritelocker);
                sharedVariable++;
               qDebug()<<sharedVariable<<" write";
                sharedVariable++;
                qDebug()<<sharedVariable<<" write";
            }
        }
    });

    QThread * thread2 = QThread::create([&]()
    {

        QString temp;
        for(int i=0;i<150;i++)
        {
           QReadLocker lock(&readwritelocker);
            qDebug()<<sharedVariable<<" read";
        }

    });

    thread1->start();
    thread2->start();
    thread1->wait();
    thread2->wait();


    return a.exec();
}























