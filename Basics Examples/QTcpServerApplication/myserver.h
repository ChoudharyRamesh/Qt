#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include<QTcpServer>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);
public slots:
    void slotOnNewConnection();

signals:
private:
    QTcpServer * server;

};

#endif // MYSERVER_H
