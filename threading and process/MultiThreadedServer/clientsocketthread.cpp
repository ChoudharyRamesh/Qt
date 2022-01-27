#include "clientsocketthread.h"
#include<QThread>
#include<iostream>
#include<string>

ClientSocketThread::ClientSocketThread(qintptr socketDescripter )
{
    this->socketDescripter =socketDescripter;

}

void ClientSocketThread::processOnThreadStart()
{
    socket = new QTcpSocket(this);
    if(!socket->setSocketDescriptor(socketDescripter))
    {
        qDebug()<<"error occured ";
        qDebug()<<socket->error();
        return;
    }
    connect(socket,&QTcpSocket::disconnected,this,&ClientSocketThread::slotOnDisconnect);
    connect(socket,&QTcpSocket::bytesWritten,this,&ClientSocketThread::slotOnDataWritten);
    connect(socket,&QTcpSocket::readyRead,this,&ClientSocketThread::slotOnDataReadytoRead);
}


ClientSocketThread::~ClientSocketThread()
{
    qDebug()<<"SOCKET  DELETED";
}

void ClientSocketThread::slotOnDisconnect()
{
    qDebug()<<"client disconnected..";
    this->thread()->exit(0);
}

void ClientSocketThread::slotOnDataWritten(qint64 bytes)
{
    qDebug()<<"bytes wrote for client"<<bytes;
}

void ClientSocketThread::slotOnDataReadytoRead()
{
    QByteArray var;
    while(socket->canReadLine())
    {
        var = socket->readLine();
        qDebug()<<"reply from client "<<var.remove(var.size()-2,2);;
    }

//    std::string temp;
//    std::cin>>temp;
//    socket->write("reply from server "+QString::fromStdString(temp).toUtf8()+"\n\r");

//        if(var=="\r\n")
//        {
            socket->write("HTTP/1.1\r\n");
            socket->write("Connection: Keep-Alive\r\n");
            socket->write("Keep-Alive: timeout=6, max=4\r\n");
            socket->write("Content-Length: 580\r\n");
            socket->write("\r\n");

            socket->write("<!DOCTYPE html>\
                          <html>\
                          <body>\
                          \
                          <h2>Images from fb server</h2>\
                          \
                          <img src=\"https://scontent.fbom8-1.fna.fbcdn.net/v/t1.0-9/74274955_1237994239733785_4133151431005831168_o.jpg?_nc_cat=104&_nc_sid=09cbfe&_nc_ohc=NB0-lEOpM-EAX9Fxz7I&_nc_ht=scontent.fbom8-1.fna&oh=45a91ed69ecf635d8e962842c8d9bdbd&oe=5F8BBDC6\" alt=\"thecodepanel.com\" style=\"width:580px;height:800px;\">\
                    \
                    </body>\
                    </html>\r\n");
                    // socket->flush();
//        }


}
