#ifndef WORKER_H
#define WORKER_H

#include<QRunnable>

class Worker : public QRunnable
{

public:
    explicit Worker();
    ~Worker();
    void run() override;

};

#endif // WORKER_H
