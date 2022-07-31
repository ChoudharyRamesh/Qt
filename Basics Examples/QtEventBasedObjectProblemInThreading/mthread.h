#ifndef MTHREAD_H
#define MTHREAD_H
#include<QThread>
#include<QTimer>

class mThread : public QThread
{
public:
    mThread();
    void run() override;
private:
    QTimer * mtimer;
    int count;
public slots:
    void increaseCount();
};

#endif // MTHREAD_H
