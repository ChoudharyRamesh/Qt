#include "mytimer.h"
#include "ui_mytimer.h"
#include<QDebug>

MyTimer::MyTimer(qint64 milisec,QWidget *parent):QWidget(parent)
{
    ui->setupUi(this);
    this->milisec=milisec;
    timer = new QTimer(this);
    timer->setInterval(10);
    ui->label->setText("00:00:00:000");
    connect(timer,&QTimer::timeout,[=]()
    {
        ui->label->setText(elaspedTime().toString("hh:mm:ss:zzz"));
    });

    start();
    pause(); resume();
}

void MyTimer::start()
{
    isPaused = false;
    elapsedTimer.start();
    timer->start();
}

void MyTimer::restart(qint64 milisec)
{
     isPaused = false;
     this->milisec=milisec;
     timer->stop();
     elapsedTimer.restart();
     timer->start();
}

void MyTimer::pause()
{
    if(isPaused==false)
    {
        isPaused = true;
        timer->stop();
        milisec = milisec + elapsedTimer.elapsed();
    }
}

void MyTimer::resume()
{
    if(isPaused==true)
    {   elapsedTimer.restart();
         isPaused = false;
         timer->start();
    }
}

QTime MyTimer::elaspedTime()
{
   if(!isPaused)
     {   qint64 secs = milisec + elapsedTimer.elapsed();
          return QTime::fromMSecsSinceStartOfDay(secs);
    }
  else return QTime::fromMSecsSinceStartOfDay(milisec);
}

MyTimer::~MyTimer()
{
    delete ui;
}



