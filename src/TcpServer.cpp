#include "TcpServer.hpp"

TcpServer::TcpServer()
{
    connect(&server_, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    server_.listen(QHostAddress::Any, 12345);
    qDebug() << "TcpServer initialized. Listening...";
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
    qDebug() << "Data written to sockets";
}

void TcpServer::onNewConnection()
{
    auto socket = server_.nextPendingConnection();
    auto ipAddress = socket->peerAddress();
    sockets_[ipAddress] = socket;
    connect(sockets_[ipAddress], &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    qDebug() << "New socket connected. IP: " << ipAddress.toString();
}

void TcpServer::onReadyRead()
{
    qDebug() << "Received new message";
    for(auto it = sockets_.begin(), end = sockets_.end(); it != end; it++)
    {
        const auto message = it.value()->readAll();
        if(not message.isEmpty())
        {
            emit sendToQml("[" + it.key().toString() + "] " + message);
            sendMessage(message);
        }
    }
}

void TcpServer::onDisconnected()
{
    const auto socket = qobject_cast<QTcpSocket*>(sender());
    if(socket != nullptr)
    {
        sockets_.remove(socket->peerAddress());
    }
}
