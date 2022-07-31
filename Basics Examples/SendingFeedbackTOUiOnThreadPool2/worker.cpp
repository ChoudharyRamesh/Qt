#include "worker.h"
#include<QDebug>
#include<QMetaObject>

Worker::Worker(QObject * reciever):reciever(reciever)
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
    // ithis is filling event loop queue ( increase one zero can cause  App not responding)
    for(int i=1;i<100000;i++)
      QMetaObject::invokeMethod(reciever,"updateProgress",Qt::QueuedConnection,Q_ARG(int,i));
}
