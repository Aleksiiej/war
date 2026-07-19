#include "TcpServer.hpp"
#include <iostream>

TcpServer::TcpServer()
{
    connect(&server_, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    emit sendToQml("TcpServer initialized. Listening...");
    server_.listen(QHostAddress::Any, port_);
}

TcpServer::~TcpServer()
{
    for(auto it = sockets_.begin(), end = sockets_.end(); it != end; it++)
    {
        it.value()->abort();
    }
}

void TcpServer::addMessage(const QString& msg)
{
    messages_.append(msg);
}

void TcpServer::sendMessage(const QString& message)
{
    for(auto it = sockets_.begin(), end = sockets_.end(); it != end; it++)
    {
        it.value()->write(message.toUtf8());
        it.value()->flush();
    }
    emit sendToQml(message);
}

const QString& TcpServer::getUsername()
{
    return username_;
}

void TcpServer::setUsername(const QString& username)
{
    username_ = username;
}

void TcpServer::onNewConnection()
{
    auto socket = server_.nextPendingConnection();
    auto ipAddress = socket->peerAddress();
    sockets_[ipAddress] = socket;
    connect(sockets_[ipAddress], &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(sockets_[ipAddress], &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
    emit sendToQml("New user connected. IP: " + ipAddress.toString());
}

void TcpServer::onReadyRead()
{
    auto socket = qobject_cast<QTcpSocket*>(sender());
    if(socket != nullptr)
    {
        const auto message = socket->readAll();
        if(not message.isEmpty())
        {
            sendMessage(message);
        }
    }
}

void TcpServer::onDisconnected()
{
    const auto socket = qobject_cast<QTcpSocket*>(sender());
    if(socket != nullptr)
    {
        const auto& address = socket->peerAddress();
        emit sendToQml(address.toString() + " disconnected");
        sockets_.remove(address);
    }
}
