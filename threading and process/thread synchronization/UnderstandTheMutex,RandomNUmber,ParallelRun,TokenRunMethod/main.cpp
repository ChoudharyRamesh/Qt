#include <QCoreApplication>
#include<QThread>
#include<QDebug>
#include<QTimer>
#include<QMutex>
#include<QObject>

//Note:: memory management ignored

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    volatile int num=0;
    int loop=10;

    for(int i=0;i<loop;i++)
    {  num=0;
        QThread * thread1 = QThread::create([&]()
        {
            for(int i=0;i<10000000;i++)
                num++;
        });

        QThread * thread2 = QThread::create([&]()
        {
            for(int i=0;i<10000000;i++)
                num++;
        });

        thread1->start(QThread::NormalPriority);
        thread2->start(QThread::NormalPriority);
        thread1->wait();
        thread2->wait();
        qDebug()<<num<<" "<<num%50;
    }


    // safe  mutithreading but slow   ( mutex is just a token )
    // its'take much time so number of calculation is reduced
    QMutex mutex;
    for(int i=0;i<loop;i++)
    {  num=0;
        QThread * thread1 = QThread::create([&]()
        {
            for(int i=0;i<10000;i++)
            { mutex.lock();
                num++;
                mutex.unlock();
            }
        });

        QThread * thread2 = QThread::create([&]()
        {
            for(int i=0;i<10000;i++)
            {  mutex.lock();
                num++;
                mutex.unlock();
            }
        });

        thread1->start(QThread::NormalPriority);
        thread2->start(QThread::NormalPriority);
        thread1->wait();
        thread2->wait();
        qDebug()<<num<<" "<<num%50;
    }


    // safe  mutithreading and fast
    QMutex mutex2;
    for(int i=0;i<loop;i++)
    {  num=0;
        QThread * thread1 = QThread::create([&]()
        {  int local=0;
            for(int i=0;i<10000000;i++)
                local++;

            mutex2.lock();
            num=num+local;
            mutex2.unlock();
        });

        QThread * thread2 = QThread::create([&]()
        {
            int local=0;
            for(int i=0;i<10000000;i++)
                local++;

            mutex2.lock();
            num=num+local;
            mutex2.unlock();

        });

        thread1->start(QThread::NormalPriority);
        thread2->start(QThread::NormalPriority);
        thread1->wait();
        thread2->wait();
        qDebug()<<num<<" "<<num%50;
    }

    return a.exec();
}
