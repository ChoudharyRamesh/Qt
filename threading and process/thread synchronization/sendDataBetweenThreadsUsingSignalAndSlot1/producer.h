#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>

class Producer : public QObject
{
    Q_OBJECT
public:
    explicit Producer(QObject *parent = nullptr);
    void recieveDataFromMainThread(const QString & data);
signals:
    void forwardDataToConsumerThread(const QString & data);

};

#endif // PRODUCER_H
