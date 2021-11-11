#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtConcurrent>

#include "MyObject.h"
#include "MySingleton.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<MyObject>("MyApi.Test", 1, 0, "MyObject");

    MySingleton s;
    qmlRegisterSingletonInstance("MyApi.Test", 1, 0, "MySingleton", &s);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QtConcurrent::run(QThreadPool::globalInstance(), [=](){
        // do something
        // emit somesignal();
    });

    return app.exec();
}
