#include "widget.h"
#include "ui_widget.h"

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
     Worker * worker = new Worker(this);
     worker->setAutoDelete(true);  // by default it's true
     QThreadPool::globalInstance()->start(worker,QThread::NormalPriority);
}

bool Widget::event(QEvent *event)
{
    if(event->type()==static_cast<QEvent::Type>(ProgressEvent::EventId))
    {
        ProgressEvent * pevent = static_cast<ProgressEvent *>(event);
        ui->progressBar->setValue(pevent->getProgressValue());
        return true;
    }
    else return QWidget::event(event);
}
