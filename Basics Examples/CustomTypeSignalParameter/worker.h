#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "progressnumber.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject * parent = nullptr);
    void doWork();
    ~Worker();
signals:
    void currentProgress(ProgressNumber progressNumber); // custom type
    void currentProgressInt(int);
};


#endif // WORKER_H
