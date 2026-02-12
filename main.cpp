#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/NetworkManager.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/war/qml/main.qml"_qs);
    engine.load(url);

    NetworkManager server;
    server.server_.listen(QHostAddress::Any, 12345);

    return app.exec();
}