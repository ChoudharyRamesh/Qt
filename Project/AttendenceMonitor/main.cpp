#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtAndroid>
#include<QDir>
#include "javaapi.h"

bool requestAndroidPermissions()
{
     QVector<QString> permissions(
    {
        "android.permission.WRITE_EXTERNAL_STORAGE",
        "android.permission.READ_EXTERNAL_STORAGE"
    });

    for (QString & permission : permissions)
    {
        auto result = QtAndroid::checkPermission(permission);
        if (result == QtAndroid::PermissionResult::Denied)
        {
            auto resultHash =
                    QtAndroid::requestPermissionsSync(QStringList({permission}));
            if (resultHash[permission] == QtAndroid::PermissionResult::Denied)
                return false;
        }
    }  return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // permission
    if(!requestAndroidPermissions())return -2;

    // create dir
    QDir dir("/storage/emulated/0/");
    if(!dir.exists("AttendanceMonitor"))
       dir.mkdir("AttendanceMonitor");

    qmlRegisterType<JavaApi>("JavaApi",1,0,"JavaApi");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
