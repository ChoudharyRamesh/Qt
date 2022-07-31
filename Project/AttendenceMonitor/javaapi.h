#ifndef JAVAAPI_H
#define JAVAAPI_H

#include <QObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QAndroidJniObject>

class JavaApi : public QObject
{
    Q_OBJECT
public:
    explicit JavaApi(QObject *parent = nullptr);
     Q_INVOKABLE static QJsonArray getData();
    Q_INVOKABLE static void updateData(QString jsonData);
};

#endif // JAVAAPI_H
