#include <QCoreApplication>
#include<QMutex>
#include<QThread>
#include<QDebug>
#include<QMutexLocker>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // lock shared variable in mutex
    int sharedVariable=0;
    QMutex mutex;

    QThread * thread1 = QThread::create([&]()
    {
        for(int i=0;i<100000;i++)
        {
            QMutexLocker locker(&mutex);
            sharedVariable++;
        }
    });

    QThread * thread2 = QThread::create([&]()
    {
        for(int i=0;i<100000;i++)
        {
            QMutexLocker locker(&mutex);
            sharedVariable++;
        }
    });


    thread1->start(QThread::NormalPriority);
    thread2->start(QThread::NormalPriority);
    thread1->wait();
    thread2->wait();

    qDebug()<<sharedVariable;

  // lock same piece of code in mutex
    sharedVariable=0;
   auto  sharedCode = [&]()
   {
       QMutexLocker locker(&mutex);
       for(int i=0;i<100000;i++)
       {
           sharedVariable++;
           qDebug()<<QThread::currentThread();
       }
   };

    QThread * thread3 = QThread::create(sharedCode);
   QThread * thread4 = QThread::create(sharedCode);

    thread3->start(QThread::NormalPriority);
    thread4->start(QThread::NormalPriority);
    thread3->wait();
    thread4->wait();

    qDebug()<<sharedVariable;



    return a.exec();
}
