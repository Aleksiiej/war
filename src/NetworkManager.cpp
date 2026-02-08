#include <iostream>

#include "NetworkManager.hpp"

NetworkManager::NetworkManager() : server_(std::make_shared<QTcpServer>())
{
    std::cout << "NetworkManager initialized." << std::endl;
    QObject::connect(this, &NetworkManager::dummySignal, this, &NetworkManager::dummySlot);
    QObject::connect(&(*server_), &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);
}

void NetworkManager::connectToServer(const QString& host, const int port)
{
    socket_ = new QTcpSocket();
    socket_->connectToHost(host, port);
    std::cout << "Connecting to server at " << host.toStdString() << ":" << port << std::endl;
}