#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<customitem.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CustomItem>("CustomItem",1,0,"CustomItem");
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/SceneGraphGL3/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
