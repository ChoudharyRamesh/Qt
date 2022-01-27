#include "mthread.h"
#include<QDebug>

mThread::mThread()
{
    qDebug()<<" mThread::mThread() , thread affinity"<<thread();
    qDebug()<<" mThread::mThread() , current running affinity"<<QThread::currentThread();
    count =0;
}

void mThread::increaseCount()
{
    qDebug()<<" mThread::increaseCount() , thread affinity"<<thread();
    qDebug()<<" mThread::increaseCount() , current running affinity"<<QThread::currentThread();
    if(count>=5) mtimer->stop();   // this is undefined ,this is the problem
    else { count++; qDebug()<<count; }
}

void mThread::run()
{
    mtimer = new QTimer;
    mtimer->setInterval(1000);
    connect(mtimer,&QTimer::timeout,this,&mThread::increaseCount);
    mtimer->start();
    qDebug()<<" mThread::run(), thread affinity"<<thread();
    qDebug()<<" mThread::run() , current running affinity"<<QThread::currentThread();
    exec();
}


