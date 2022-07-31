#include "worker.h"
#include<QThread>
#include<QDebug>

Worker::Worker(QObject *parent) : QObject(parent)
{
    once=true;
}


void Worker::doWork1()
{ emit workStrated();
    for(int i=1;i<=100000;i++)
    {   emit currentStatus(i); }
    emit workFinished();
    // for create thread method , no need to explicitly tell to thread that work finished
}

void Worker::doWork2()
{
    emit workStrated();
    for(int i=0;i<=100000;i++)
    {   emit currentStatus(i); }
    emit workFinished();
    // for move to thread method , need to explicitly tell to thread that work finished
    // QThread::currentThread()->quit();
    if(once)  QTimer::singleShot(2000,this,[=]()
    { static int count = 1;
        count++;
        if(count==3){ once=false; count=1; thread()->quit(); }
        doWork2();
    });
}

