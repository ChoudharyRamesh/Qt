#include "widget.h"
#include "ui_widget.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mthread = new MThread();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startButton_clicked()
{
    mthread->start();
}

void Widget::on_pauseButton_clicked()
{
    mthread->pause();
}

void Widget::on_resumeButon_clicked()
{
    mthread->resume();
}
