#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    // create socket
//    tcpSocket = new QTcpSocket(this);

//    //make connection
//    tcpSocket->connectToHost("www.google.com",80);


//    if(tcpSocket->waitForConnected(5000))
//    {
//        qDebug()<<"connected.. ";
//        // send
//        tcpSocket->write("hello server\n\r\r\n\n\r");
//        tcpSocket->waitForBytesWritten(2000);
//        tcpSocket->waitForReadyRead(2000);
//        qDebug()<<"Reading"<<tcpSocket->bytesAvailable();
//        qDebug()<<tcpSocket->readAll();
//        tcpSocket->close();
//    }
//    else
//    {
//        qDebug()<<"not conneted "<< tcpSocket->error();
//    }


}

Widget::~Widget()
{
    delete ui;
}

