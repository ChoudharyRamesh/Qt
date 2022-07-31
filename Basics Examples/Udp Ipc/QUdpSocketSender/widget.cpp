#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost,1234);
    connect(socket,&QUdpSocket::readyRead,this,&Widget::readyRead);
}

void Widget::readyRead()
{
    qint64 message_size;
    message_size = socket->pendingDatagramSize();
    QByteArray message;
    message.resize(message_size);
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(message.data(),message_size,&sender,&senderPort);
    if(message=="clear")ui->listWidget->clear();
    else
    {
    ui->listWidget->addItem(message+" "+QString::number(message_size)
                            +" "+sender.toString()+" "+QString::number(senderPort));
    }
}

Widget::~Widget()
{
    delete ui;
}

