#include <iostream>

#include "Receiver.hpp"

Receiver::Receiver()
{
    std::cout << "Receiver initialized." << std::endl;
    connect(&server_, &QTcpServer::newConnection, this, &Receiver::onNewConnection);
    server_.listen(QHostAddress::Any, 12345);
}

void Receiver::onNewConnection()
{
    std::cout << "New socket connected" << std::endl;
    socket_ = server_.nextPendingConnection();
    connect(socket_, &QTcpSocket::readyRead, this, &Receiver::onReadyRead);
}

void Receiver::onReadyRead()
{
    std::cout << "Received new message" << std::endl;
    const auto message = socket_->readAll();
    qDebug() << QString(message); 
}
