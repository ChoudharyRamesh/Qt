#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include<QRunnable>

class Worker : public QRunnable
{

public:
    explicit Worker();
    ~Worker();
    void run() override;
private:
    void doWork();
};

#endif // WORKER_H
