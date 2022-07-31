#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include<QThread>
#include<QSet>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);
    void incomingConnection(qintptr handle) override;
    QSet<QThread *>threads;
signals:

};

#endif // MYSERVER_H
