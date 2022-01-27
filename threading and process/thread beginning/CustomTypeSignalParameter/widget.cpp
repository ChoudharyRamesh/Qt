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
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startWorkButton_clicked()
{
    Worker * worker = new Worker();
    QThread * thread = new QThread;
    worker->moveToThread(thread);
    connect(thread,&QThread::started,[=]()
    {
        worker->doWork();
    });
    connect(thread,&QThread::finished,[=]()
    {
        delete worker;
        thread->deleteLater();
    });
    connect(thread,&QThread::destroyed,[=]()
    {
        qDebug()<<"thread destroyed";
    });
    connect(worker,&Worker::currentProgressInt,this,&Widget::updateProgressInt);
 //connect(worker,&Worker::currentProgress,this,&Widget::updateProgress);
    thread->start();
}

void Widget::updateProgress(ProgressNumber progressNumber)
{
    ui->progressBar->setValue(progressNumber.getProgressValue());
}

void Widget::updateProgressInt(int progress)
{
    ui->progressBar->setValue(progress);
}


