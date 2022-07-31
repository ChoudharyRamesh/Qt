#include <QCoreApplication>
#include"mthread.h"
#include<QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"main, current running affinity"<<QThread::currentThread();
    mThread thread;
    thread.start();
    return a.exec();
}
