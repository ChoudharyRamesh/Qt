#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<trianglerenderer.h>
#include<texturerenderer.h>
#include<QQuickWindow>
#include<cuberenderer.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    qmlRegisterType<Triangle>("Custom",1,0,"Triangle");
    qmlRegisterType<Texture>("Custom",1,0,"Texture");
    qmlRegisterType<Cube>("Custom",1,0,"Cube");

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

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
