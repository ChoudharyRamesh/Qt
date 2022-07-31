#include "widget.h"
#include "ui_widget.h"
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QVariantMap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    netmanager = new QNetworkAccessManager(this);
    netreply = nullptr;

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()   // fetch data button code
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://jsonplaceholder.typicode.com/posts"));
    netreply = netmanager->get(request);
    connect(netreply,&QIODevice::readyRead,this,&Widget::dataReadyToRead);
    connect(netreply,&QNetworkReply::finished,this,&Widget::dataReadFinished);
}

void Widget::dataReadyToRead()
{
   qDebug()<<"some data available";
  // bytearray.clear();
   bytearray.append(netreply->readAll());
}

void Widget::dataReadFinished()
{
     if(netreply->error())
     {
         qDebug()<<"error "<<netreply->errorString();
     }
     else
     {  static int count = 0;
         QJsonDocument doc  = QJsonDocument::fromJson(bytearray);
         qDebug()<<doc;
         QJsonArray  arr = doc.array();
         qDebug()<<"arr size is "<<arr.size();
         int i=0;
         for( i=0;i<arr.size();i++)
           {
               QJsonObject object = arr.at(i).toObject();
               QVariantMap map = object.toVariantMap();
               QString title = map["title"].toString();
               ui->listWidget->addItem(QString::number(i+1+count)+" "+title);
           }
         count = count+i;
     }
}




















