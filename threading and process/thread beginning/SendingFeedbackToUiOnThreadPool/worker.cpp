#include "worker.h"
#include<QDebug>
#include<QApplication>

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
    // ithis is filling event loop queue ( increase one zero can cause  App not responding )
    for(int i=1;i<100000;i++)
        QApplication::postEvent(reciever,new ProgressEvent(i));
}
