#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "edgefilter.h"
#include "videoproducer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<EdgeFilter>("QImageFilters", 1, 0, "EdgeFilter");
    qmlRegisterType<VideoProducer>("QImageFilters", 1, 0, "VideoProducer");

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
