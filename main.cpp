#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/TcpServer.hpp"
#include "src/Client.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/war/qml/main.qml"_qs);
    engine.load(url);

    qmlRegisterType<TcpServer>("war", 1, 0, "TcpServer");
    qmlRegisterType<Client>("war", 1, 0, "Client");

    return app.exec();
}