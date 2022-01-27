#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include<QTimer>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    void doWork1();
    void doWork2();
signals:
    void workStrated();
    void workFinished();
    void currentStatus(int a);
private:
     bool once;

};

#endif // WORKER_H
