#include "widget.h"
#include "ui_widget.h"

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


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);

    qDebug()<<"logical coordinate "<<painter.window();
    qDebug()<<"physical coordinate "<<painter.viewport();
    painter.drawRect(0,0,100,100);

    // change logical coordinate
    painter.save();

    painter.setWindow(0,0,300,200);
    pen.setColor(QColor::fromRgb(246,0,246,255));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawRect(0,0,100,100);
    qDebug()<<"logical coordinate "<<painter.window();
    qDebug()<<"physical coordinate "<<painter.viewport();

    painter.restore();
//   // restoring old setting of painter
//   painter.drawRect(250,250,50,50);

    // change physical coordinate
    painter.save();

    painter.setViewport(0,0,300,200);
    pen.setColor(Qt::blue);
    pen.setWidth(10);
    painter.setPen(pen);
    painter.drawRect(0,0,100,100);
    qDebug()<<"logical coordinate "<<painter.window();
    qDebug()<<"physical coordinate "<<painter.viewport();

    painter.restore();

}
















