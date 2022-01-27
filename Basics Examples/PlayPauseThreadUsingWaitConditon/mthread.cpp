#include "mthread.h"

MThread::MThread():state(IDLE)
{
    connect(this,&MThread::started,[=]()
    {
        mMutex.lock();
        state = RUNNING;
        mMutex.unlock();
    });
}

void MThread::resume()
{
     mMutex.lock();
    if( state==PAUSED  && !isFinished() )
    {
        state=RUNNING;
        playPauseController.wakeAll();
    }
    mMutex.unlock();
}

void MThread::pause()
{
    mMutex.lock();
    if( state==RUNNING && !isFinished() )
      state = PAUSED;
    mMutex.unlock();
}

void MThread::run()
{
    for(int i=0;i<100000;i++)
    {
        mMutex.lock();
        if( state == PAUSED ) playPauseController.wait(&mMutex);
        mMutex.unlock();

        qDebug()<<" thread "<<i;
    }
}


