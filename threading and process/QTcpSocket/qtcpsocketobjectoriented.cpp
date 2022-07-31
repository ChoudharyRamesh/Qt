#include "qtcpsocketobjectoriented.h"

Qtcpsocketobjectoriented::Qtcpsocketobjectoriented(QObject *parent):QObject(parent)
{
    setThingsup();
}

void Qtcpsocketobjectoriented::setThingsup()
{
    socket = new QTcpSocket(this);

    connect(socket,&QTcpSocket::connected,this,&Qtcpsocketobjectoriented::slotOnConnect);
    connect(socket,&QTcpSocket::disconnected,this,&Qtcpsocketobjectoriented::slotOnDisconnect);
    connect(socket,&QTcpSocket::bytesWritten,this,&Qtcpsocketobjectoriented::slotOnDataWritten);
    connect(socket,&QTcpSocket::readyRead,this,&Qtcpsocketobjectoriented::slotOnDataReadytoRead);

    qDebug()<<"connecting ... ";
    socket->connectToHost("www.google.com",80,QIODevice::ReadWrite);
    if(!socket->waitForConnected(2000))
    {
        qDebug()<<" not connected "<<socket->error();
    }
}

void Qtcpsocketobjectoriented::slotOnConnect()
{
    qDebug()<<"connected..";
    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n");
}

void Qtcpsocketobjectoriented::slotOnDisconnect()
{
    qDebug()<<"disconnected..";
}

void Qtcpsocketobjectoriented::slotOnDataWritten(qint64 bytes)
{
    qDebug()<<"bytes wrote "<<bytes;
}

void Qtcpsocketobjectoriented::slotOnDataReadytoRead()
{
    qDebug()<<"ready to read data "<<socket->readAll();
}
