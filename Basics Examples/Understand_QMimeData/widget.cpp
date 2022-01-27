#include "widget.h"
#include "ui_widget.h"
#include<QByteArray>
#include<QPixmap>
#include<QBuffer>
#include<QDebug>
#include<QVariant>
#include<QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QMimeData * newdata = new QMimeData;
    QPixmap pixmap("E:/pic3.png");
//    qDebug()<<"pixmap data is "<<pixmap;
    QByteArray bytearray;
    QBuffer buffer(&bytearray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
  //  newdata->setImageData(QVariant(bytearray));
//      qDebug()<<"pixmap data inside byte array "<<bytearray;
     newdata->setData("image/ *",bytearray);
    qDebug()<<"mime data is "<<newdata->html();
    QLabel * label = new QLabel;
  //  QPixmap map; map.loadFromData(newdata->imageData().toByteArray());
    QPixmap map; map.loadFromData(newdata->data("image/ *"));
    label->setPixmap(map);
    label->setParent(this);
    //label->setPixmap()

//   const char array []= {'h','e','x','\0','x','o'};
//   QByteArray ba4(QByteArray::fromRawData("hex\0xo",6));
//   qDebug()<<ba4.size();
//   qDebug()<<ba4.at(3);
//   QByteArray ba("hex\0xo");
//   qDebug()<<qstrlen(ba);
//   qDebug()<<ba.at(3);
}

Widget::~Widget()
{
    delete ui;
}

