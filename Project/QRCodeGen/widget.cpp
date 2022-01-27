#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<iostream>
#include<QtSvg>
#include<QPainter>
#include<QFile>
#include<QPen>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{

    auto var = qrcodegen::QrCode::encodeText(ui->lineEdit->text().toLatin1(),qrcodegen::QrCode::Ecc::HIGH);
    QPixmap pixmap(1000,1000);
    QPainter painter(&pixmap);
    QSvgRenderer svgrender(QByteArray::fromStdString(var.toSvgString(10)));
    svgrender.render(&painter);
    ui->label->setPixmap(pixmap.scaled(800,800));
    ui->label->setAlignment(Qt::AlignCenter);
//    QFile file("C:/Users/Nishant Choudhary/Desktop/Qr.jpg");
//    file.open(QFile::ReadOnly);
    pixmap.save("C:/Users/Nishant Choudhary/Desktop/Qr.jpg");
}
