#include "temp.h"

Temp::Temp(QObject *parent) : QObject(parent)
{

}

void Temp::hideBannerAd()
{
    QtAndroid::runOnAndroidThread([=]()
     {
       QAndroidJniObject::callStaticMethod<void>(
                "com/qtadmob/ShareShot/QtAdMob",
                "hideBannerAd",
                "()V");
    });
}

void Temp::showBannerAd()
{
    QtAndroid::runOnAndroidThread([=]()
    {
       QAndroidJniObject::callStaticMethod<void>(
                "com/qtadmob/ShareShot/QtAdMob",
                "showBannerAd",
                "()V");
    });
}






