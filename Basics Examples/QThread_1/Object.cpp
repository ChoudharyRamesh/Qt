#include "Object.h"

MyObject::MyObject(QObject *parent ):QObject(parent)
{

}
void MyObject::doSetup(QThread & ref)
{
    connect(&ref,&QThread::started,this,&MyObject::doWork);
    thread =&ref;
}
void MyObject::doWork()
{
    for(int i=0;i<10;i++)
    {
        qDebug()<<i;
        QThread::msleep(300);
        if(i==9)thread->terminate();

        /*
         * QMutex mutex;
         * mutext lock
         * some operation on shared varaible
         * */

    }
}
