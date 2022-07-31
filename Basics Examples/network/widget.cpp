#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    netManager = new QNetworkAccessManager(this);
    netreply = nullptr;
    bytearray = new QByteArray();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    // network request
    ui->textEdit->clear();
    if(bytearray->size()>0) bytearray->clear();
    QNetworkRequest request;
    request.setUrl(QUrl(ui->lineEdit->text()));
    netreply = netManager->get(request);
    connect(netreply,&QIODevice::readyRead,this,&Widget::dataReadyToRead);
    connect(netreply,&QNetworkReply::finished,this,&Widget::dataReadFinished);
}

void Widget::dataReadyToRead()
{
   qDebug()<<"some data available";
   bytearray->append(netreply->readAll());
}

void Widget::dataReadFinished()
{
     if(netreply->error())
     {
         qDebug()<<"error "<<netreply->errorString();
     }
     else
     {
        // ui->textEdit->setPlainText(QString(*bytearray));
         ui->textEdit->setHtml(QString(*bytearray));
         disconnect(netreply,&QIODevice::readyRead,this,&Widget::dataReadyToRead);
         disconnect(netreply,&QNetworkReply::finished,this,&Widget::dataReadFinished);
     }
}















