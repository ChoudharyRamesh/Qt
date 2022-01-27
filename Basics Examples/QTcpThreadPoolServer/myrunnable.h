#ifndef MYRUNNABLE_H
#define MYRUNNABLE_H

#include<QRunnable>
#include<QTcpSocket>
#include<QDebug>

class MyRunnable :public QRunnable
{

public:
    MyRunnable(qintptr socketDescripter);
    ~MyRunnable();
    void run() override;
private:
    qintptr socketDescripter;
};

#endif // MYRUNNABLE_H
