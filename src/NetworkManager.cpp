#include <iostream>

#include "NetworkManager.hpp"

NetworkManager::NetworkManager() : socket_(new QTcpSocket)
{
    std::cout << "NetworkManager initialized." << std::endl;
    QObject::connect(&server_, &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);
}

void NetworkManager::connectToServer(const QString& host, const int port)
{
    socket_->connectToHost(host, port);
    std::cout << "Connecting to server at " << host.toStdString() << ":" << port << std::endl;
    if (socket_->waitForConnected(3000))
    {
        qDebug() << "Connection succes";
    }
    else
    {
        qDebug() << "Connection failed";
    }
}

void NetworkManager::sendMessage(QString&& message)
{
    // QDataStream out(socket_);
    // socket_ << message;
    // socket_->write(message.data());
    std::cout << "Data written to socket by sender" << std::endl;
}
