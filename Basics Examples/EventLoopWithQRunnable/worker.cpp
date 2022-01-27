#include "worker.h"
#include<QEventLoop>
#include<QTimer>
#include<QDebug>
#include<QObject>

Worker::Worker()
{

}

Worker::~Worker()
{
  qDebug()<<"worker deleted";
}

void Worker::run()
{
    QEventLoop loop;
    static int exit=0;
    QTimer timer;
    timer.setInterval(2000);
    QObject::connect(&timer,&QTimer::timeout,[&]()
    {  exit++;
        qDebug()<<"it's working";
        if(exit==5) loop.exit(0);
    });
    timer.start();
    loop.exec();
}
