#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include<QRunnable>
#include "progressevent.h"

class Worker : public QRunnable
{

public:
    explicit Worker(QObject * reciever);
    ~Worker();
    void run() override;
private:
    void doWork();
    QObject * reciever;
};

#endif // WORKER_H
