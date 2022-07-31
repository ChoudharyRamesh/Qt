#ifndef TEMP_H
#define TEMP_H

#include <QObject>
#include<QAndroidJniObject>
#include<QtAndroid>

class Temp : public QObject
{
    Q_OBJECT
public:
    explicit Temp(QObject *parent = nullptr);
     Q_INVOKABLE void hideBannerAd();
     Q_INVOKABLE void showBannerAd();

signals:

};

#endif // TEMP_H
