#include "worker.h"
#include<QDebug>
#include<QTimer>

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
    QTimer::singleShot(3000,[]()
    {
       for(int i=0;i<5;i++)
            qDebug()<<"asynch running";
    });
    qDebug()<<"work finished";
}

