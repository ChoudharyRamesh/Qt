#include "widget.h"
#include "ui_widget.h"
#include<QThread>
#include "worker.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setRange(1,100000);
    ui->progressBar->setValue(10000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_createMethodButton_clicked()
{
    // reset for reclick
    ui->progressBar->setValue(0);

    Worker * worker = new Worker;
    connect(worker,&Worker::workFinished,[=]()
    {
        qDebug()<<"work finished";
        worker->deleteLater();
    });

    connect(worker,&Worker::destroyed,[]()
    {
        qDebug()<<"worker deleted";

    });

    connect(worker,&Worker::workStrated,[]()
    {
        qDebug()<<"work started";
    });
    connect(worker,&Worker::currentStatus,[=](int value)
    {
        ui->progressBar->setValue(value);
    });
    QThread * thread = QThread::create([=](){ worker->doWork1();});
    connect(thread,&QThread::finished,thread,&QThread::deleteLater);
    connect(thread,&QThread::destroyed,[]()
    {
        qDebug()<<"thread deleted";

    });
    thread->start();
}

void Widget::on_moveToThreadButton_clicked()
{
    // reset for reclick
    ui->progressBar->setValue(0);

    Worker * worker = new Worker;
    connect(worker,&Worker::workFinished,[=]()
    {
        qDebug()<<"work finished";
    });

    connect(worker,&Worker::destroyed,[]()
    {
        qDebug()<<"worker deleted";
    });

    connect(worker,&Worker::workStrated,[]()
    {
        qDebug()<<"work started";
    });

    connect(worker,&Worker::currentStatus,[=](int value)
    {
        ui->progressBar->setValue(value);
    });
    QThread * thread = new QThread(this);
    connect(thread,&QThread::finished,thread,[=]()
    {
        delete worker;
        thread->deleteLater();
    });

    worker->moveToThread(thread);
    connect(thread,&QThread::started,[=]()
    {
       worker->doWork2();

    });
    connect(thread,&QThread::destroyed,[]()
    {
        qDebug()<<"thread deleted";

    });
    thread->start();

}
