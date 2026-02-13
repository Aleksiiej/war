#include "Receiver.hpp"

Receiver::Receiver()
{
    qDebug() << "Receiver initialized.";
    connect(&server_, &QTcpServer::newConnection, this, &Receiver::onNewConnection);
    server_.listen(QHostAddress::Any, 12345);
}

void Receiver::onNewConnection()
{
    qDebug() << "New socket connected";
    socket_ = server_.nextPendingConnection();
    connect(socket_, &QTcpSocket::readyRead, this, &Receiver::onReadyRead);
}

void Receiver::onReadyRead()
{
    qDebug() << "Received new message";
    const auto message = socket_->readAll();
    qDebug() << QString(message); 
}
