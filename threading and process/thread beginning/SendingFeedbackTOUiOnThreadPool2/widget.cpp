#include "widget.h"
#include "ui_widget.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setRange(1,100000);
    ui->progressBar->setValue(0);
    qDebug()<<QThreadPool::globalInstance()->maxThreadCount();
    qDebug()<<QThreadPool::globalInstance()->activeThreadCount();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startWorkButton_clicked()
{
    Worker * worker = new Worker(this);
    worker->setAutoDelete(true);  // by default it's true
    QThreadPool::globalInstance()->start(worker,QThread::NormalPriority);
}

void Widget::updateProgress(int progress)
{
    ui->progressBar->setValue(progress);
}

