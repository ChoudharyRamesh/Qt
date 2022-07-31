#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include<QThreadPool>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);
    void incomingConnection(qintptr handle) override;

};

#endif // MYSERVER_H
