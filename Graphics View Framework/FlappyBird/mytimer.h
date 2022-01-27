#ifndef MYTIMER_H
#define MYTIMER_H
#include<QTime>
#include<QElapsedTimer>
class MyTimer
{
    public:
    MyTimer(qint64 milisec=0);
    void start();
    void restart(qint64 milisec=0);
    void pause();
    void resume();
    QTime elaspedTime();
   ~MyTimer();

private:
    qint64 milisec;
    QElapsedTimer elapsedTimer;
    bool isPaused;
    QTime clock;
};

#endif // MYTIMER_H
