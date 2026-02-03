#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/TcpServer.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/war/qml/main.qml"_qs);
    engine.load(url);

    TcpServer server;

    return app.exec();
}