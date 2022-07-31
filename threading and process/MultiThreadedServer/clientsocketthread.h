#ifndef CLIENTSOCKETTHREAD_H
#define CLIENTSOCKETTHREAD_H
#include<QObject>
#include<QTcpSocket>
#include<QDebug>

class ClientSocketThread:public QObject
{
    Q_OBJECT
public:
    explicit ClientSocketThread(qintptr socketDescripter);
   ~ClientSocketThread();
public slots:
    void processOnThreadStart();
    void slotOnDisconnect();
    void slotOnDataWritten(qint64 bytes);
    void slotOnDataReadytoRead();
private:
    QTcpSocket * socket;
    qintptr socketDescripter;
};



#endif // CLIENTSOCKETTHREAD_H
