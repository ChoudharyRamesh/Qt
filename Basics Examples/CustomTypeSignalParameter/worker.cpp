#include "worker.h"
#include<QDebug>
#include<QMetaObject>
#include<QThread>

Worker::Worker(QObject * parent ):QObject(parent)
{

}

Worker::~Worker()
{
  qDebug()<<"worker destroyed";
}

void Worker::doWork()
{

    qDebug()<<"work started";
    for(int i=1;i<100000;i++)
        emit currentProgressInt(i);
     // emit currentProgress(ProgressNumber(i));
    qDebug()<<"work finished";
     QThread::currentThread()->exit(0);
}
