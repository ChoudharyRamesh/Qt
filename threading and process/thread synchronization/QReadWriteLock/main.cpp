#include <QCoreApplication>
#include<QFile>
#include<QDataStream>
#include<QDebug>
#include<QThread>
#include<QReadWriteLock>

// mutex at a time one reader hi allow karta hai jabki readwritelocker mai at a time kai sare readers ho sakte
// hai , yahi 10 readers read kar rahe hai write karne wale method ko queue mai rhn padega , or jab writing
// perform ho rahi hai to readers and incoming writeres dono ko queue mai rahna padega
// but mutex mai aesa nhi hai mutex mai at a time one readers hi allow hai.

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
               readwritelocker.lockForWrite();
                  qDebug()<<sharedVariable<<" write";
                sharedVariable++;
                qDebug()<<sharedVariable<<" write";
               readwritelocker.unlock();
            }
        }
    });

    QThread * thread2 = QThread::create([&]()
    {

        QString temp;
        for(int i=0;i<150;i++)
        {
            readwritelocker.lockForRead();
            qDebug()<<sharedVariable<<" read";
            readwritelocker.unlock();
        }

    });

    thread1->start();
    thread2->start();
    thread1->wait();
    thread2->wait();


    return a.exec();
}























