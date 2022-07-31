#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QMouseEvent>
#include<QMenu>

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

bool Widget::event(QEvent *event)
{
    qDebug()<<"event is ocured "<<event->type();
    return false;
}

