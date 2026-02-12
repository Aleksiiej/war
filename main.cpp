#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/Receiver.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/war/qml/main.qml"_qs);
    engine.load(url);

    Receiver server;

    return app.exec();
}