#include "myserver.h"
#include "myrunnable.h"
#include<QThread>
#include<QTcpSocket>

MyServer::MyServer(QObject *parent) : QTcpServer(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);

    if(this->listen(QHostAddress::Any,12345))
    {
        qDebug()<<"srever started";
    }
    else
    {
        qDebug()<<this->errorString();
    }
}



void MyServer::incomingConnection(qintptr handle)
{
    qDebug()<<"new connection";
    static int i=0;
    qDebug()<<i++;

    MyRunnable * task = new MyRunnable(handle);
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);

}
