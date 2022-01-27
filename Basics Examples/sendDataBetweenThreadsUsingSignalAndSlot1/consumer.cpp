#include "consumer.h"
#include<QDebug>
#include<QThread>

Consumer::Consumer(QObject *parent) : QObject(parent)
{

}

void Consumer::recieveDataFromProducerThread(const QString & data)
{
    qDebug()<<"Consumer::recieveDataFromProducerThread,running-thread ="<<QThread::currentThread();
    qDebug()<<"Consumer::recieveDataFromProducerThread ,object leaving="<<thread();
   emit sendBacktoUi(data);
}

