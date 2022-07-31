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


void Widget::on_startWorkButton_clicked()
{
     Worker * worker = new Worker;
     worker->setAutoDelete(true);  // by default it's true
     QThreadPool::globalInstance()->start(worker,QThread::NormalPriority);
}
