#include "myserver.h"
#include "clientsocketthread.h"
#include<QThread>

MyServer::MyServer(QObject *parent) : QTcpServer(parent)
{
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
    system("cls");
   for(auto it: threads)
        if(it->isRunning()) qDebug()<<it<<" is running ";


    if(threads.size()>=5)
    {
        qDebug()<<" please wait ,maximum limit reached";
        QTcpSocket tempsocket;
        tempsocket.setSocketDescriptor(handle);
        tempsocket.write("HTTP/1.1 200 OK\r\n");
        tempsocket.write("\r\n");
        tempsocket.write("<!DOCTYPE html>\
                         <html>\
                         <head>\
                         <title>Server Overflow</title>\
                         <style>\
                         body {\
                           background-color: black;\
                           text-align: center;\
                           color: white;\
                           font-family: Arial, Helvetica, sans-serif;\
                         }\
                         </style>\
                         </head>\
                         <body>\
                         \
                         <h1>Plese wait,server is running out of resources</h1>\
                         \
                         </body>\
                         </html>\n\r");
        tempsocket.waitForBytesWritten(1500);
        return;
    }

    qDebug()<<"new connection";
    QThread * newThread = new QThread();
    threads.insert(newThread);
    ClientSocketThread * newSocketForThread =  new ClientSocketThread(handle);
    connect(newThread,&QThread::finished,newThread,[=]()
    {
        threads.remove(newThread);
        newThread->deleteLater();
        newSocketForThread->deleteLater();

    });

    connect(newThread,&QThread::started,newSocketForThread,&ClientSocketThread::processOnThreadStart);
    newSocketForThread->moveToThread(newThread);
    newThread->start();
}
