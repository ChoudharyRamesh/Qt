#include "worker.h"
#include<QDebug>

Worker::Worker()
{

}

Worker::~Worker()
{
  qDebug()<<"worker destroyed";
}

void Worker::run()
{
    qDebug()<<"work started";
    doWork();
    qDebug()<<"work finished";
}

void Worker::doWork()
{
    for(int i=0;i<10000;i++)
        qDebug()<<i;
}
