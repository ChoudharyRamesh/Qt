#include <QCoreApplication>
#include "Object.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThread thread1;
    QThread thread2;
    QThread thread3;

    MyObject obj1;
    MyObject obj2;
    MyObject obj3;
    obj1.doSetup(thread1);
    obj1.moveToThread(&thread1);
    obj2.doSetup(thread2);
    obj2.moveToThread(&thread2);
    obj3.doSetup(thread3);
    obj3.moveToThread(&thread3);
    // thread1.start(QThread::HighestPriority);
    thread1.start(); thread1.wait();
    thread2.start();
    thread3.start();
    return a.exec();
}
