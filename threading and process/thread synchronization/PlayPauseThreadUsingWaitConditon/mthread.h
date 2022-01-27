#ifndef MTHREAD_H
#define MTHREAD_H

#include<QWaitCondition>
#include<QThread>
#include<QDebug>
#include<QMutex>
#include<QFunctionPointer>
#include<QDebug>

class MThread:public QThread
{
public:
    MThread();
public slots:
    void resume();
    void pause();
    void run() override;

private:

   enum STATE{ RUNNING,PAUSED,IDLE };
   QWaitCondition playPauseController;
   QMutex mMutex;
   STATE state;

};


#endif // MTHREAD_H
