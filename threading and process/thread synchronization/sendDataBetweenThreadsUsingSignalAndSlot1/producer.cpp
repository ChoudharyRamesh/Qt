#include "producer.h"
#include<QDebug>
#include<QThread>

Producer::Producer(QObject *parent) : QObject(parent)
{
}

void Producer::recieveDataFromMainThread(const QString &data)
{
    qDebug()<<"Producer::recieveDataFromMainThread,running-thread ="<<QThread::currentThread();
    qDebug()<<"Producer::recieveDataFromMainThread ,object leaving="<<thread();
    emit forwardDataToConsumerThread(data);
}


