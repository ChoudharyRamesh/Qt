#include "mytimer.h"

MyTimer::MyTimer(qint64 milisec)
{
    this->milisec=milisec;
}

void MyTimer::start()
{
  isPaused = false;
  elapsedTimer.start();
}

void MyTimer::restart(qint64 milisec)
{
    isPaused = false;
    this->milisec=milisec;
    elapsedTimer.restart();
}

void MyTimer::pause()
{
    if(isPaused==false)
    {
        isPaused = true;
        milisec = milisec + elapsedTimer.elapsed();
    }
}

void MyTimer::resume()
{
    if(isPaused==true)
    {   elapsedTimer.restart();
         isPaused = false;
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

}


