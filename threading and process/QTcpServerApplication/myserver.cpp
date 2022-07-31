#include "myserver.h"
#include<QTcpSocket>
#include<QThread>

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server,&QTcpServer::newConnection,this,&MyServer::slotOnNewConnection);
    if(server->listen(QHostAddress::Any,12345))
    {
        qDebug()<<"srever started";
    }
    else
    {
        qDebug()<<server->errorString();
    }
}

void MyServer::slotOnNewConnection()
{
    qDebug()<<"new connection";
    QTcpSocket * temp = server->nextPendingConnection();
    temp->write("hello client \n\r\n\r\n\r");
  //  temp->close();
}
