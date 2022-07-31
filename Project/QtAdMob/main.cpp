#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QAndroidJniObject>
#include<QtAndroid>
#include "temp.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Temp>("Temp",1,0,"Temp");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QtAndroid::runOnAndroidThread([=]()
    {
        QAndroidJniObject::callStaticMethod<void>(
                  "com/qtadmob/ShareShot/QtAdMob",
                  "initializeMobiledAdsSdk",
                  "(Landroid/content/Context;Landroid/app/Activity;)V",
                  QtAndroid::androidContext().object(),QtAndroid::androidActivity().object());
     });


    QObject::connect(&app,&QGuiApplication::applicationStateChanged,[&]
         (Qt::ApplicationState state)
    {
        if(state==Qt::ApplicationState::ApplicationInactive)
        {
            QAndroidJniObject::callStaticMethod<void>(
                      "com/qtadmob/ShareShot/QtAdMob",
                      "setActivityVisibility",
                      "(Z)V",
                      false);

        }
        if(state==Qt::ApplicationState::ApplicationActive)
        {
            QAndroidJniObject::callStaticMethod<void>(
                      "com/qtadmob/ShareShot/QtAdMob",
                      "setActivityVisibility",
                      "(Z)V",
                      true);
        }
    });

    return app.exec();
}
