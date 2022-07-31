#ifndef QTCPSOCKETOBJECTORIENTED_H
#define QTCPSOCKETOBJECTORIENTED_H

#include<QObject>
#include<QTcpSocket>
#include<QDebug>

class Qtcpsocketobjectoriented:public QObject
{
    Q_OBJECT
public:
    Qtcpsocketobjectoriented(QObject * parent = nullptr);


public slots:
    void setThingsup();
    void slotOnConnect();
    void slotOnDisconnect();
    void slotOnDataWritten(qint64 bytes);
    void slotOnDataReadytoRead();


private:
    QTcpSocket * socket;
};

#endif // QTCPSOCKETOBJECTORIENTED_H
