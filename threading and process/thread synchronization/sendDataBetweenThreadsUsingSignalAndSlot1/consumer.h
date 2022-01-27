#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>

class Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = nullptr);
public slots:
    void recieveDataFromProducerThread(const QString &);
signals:
   void sendBacktoUi(const QString &);
};

#endif // CONSUMER_H
