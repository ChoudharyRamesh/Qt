#include <QCoreApplication>
#include<atomic>
#include<QThread>
#include<QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::atomic<int> sharedInteger;
    sharedInteger.store(0);

// int sharedInteger = 0;

    QThread * thread1 = QThread::create([&]()
    { for(int i=0;i<1000000;i++)
        sharedInteger++;
    });
    QThread * thread2 = QThread::create([&]()
    { for(int i=0;i<1000000;i++)
        sharedInteger++;
    });

    thread1->start();
    thread2->start();
    thread1->wait();
    thread2->wait();

    qDebug()<<sharedInteger;
    return a.exec();
}
