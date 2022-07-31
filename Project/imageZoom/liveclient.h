#ifndef LIVECLIENT_H
#define LIVECLIENT_H
#include <QObject>
#include <QQmlApplicationEngine>

class LiveClient:public QObject
{
    Q_OBJECT
public:
    LiveClient(QObject* parent = Q_NULLPTR);
    ~LiveClient(){};

    Q_INVOKABLE void loadQml();
    void setEngine(QQmlApplicationEngine *engine) { m_engine = engine; }

private:
    QQmlApplicationEngine* m_engine;
};

#endif // LIVECLIENT_H
