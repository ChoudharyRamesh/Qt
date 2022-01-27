#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QThread>
#include<QDebug>

class MyObject:public QObject
{
    Q_OBJECT
public:
    MyObject(QObject * parent = nullptr);
    void doWork();
    QThread * thread;
    void doSetup(QThread & ref);

};


#endif // MYTHREAD_H
