#include <iostream>

#include "Sender.hpp"

Sender::Sender() : socket_(new QTcpSocket)
{
    std::cout << "Sender initialized." << std::endl;
}

void Sender::connectToServer(const QString& host, const int port)
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

void Sender::sendMessage(QString message)
{
    socket_->write(message.toUtf8());
    std::cout << "Data written to socket by sender" << std::endl;
}