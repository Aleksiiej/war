#include "TcpServer.hpp"

TcpServer::TcpServer()
{
    qDebug() << "TcpServer initialized.";
    connect(&server_, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    server_.listen(QHostAddress::Any, 12345);
}

void TcpServer::addMessage(const QString& msg)
{
    messages_.append(msg);
}

QString& TcpServer::getLastMessage()
{
    return messages_.last();
}

void TcpServer::sendMessage(const QString& message)
{
    socket_->write(message.toUtf8());
    socket_->flush();
    qDebug() << "Data written to socket";
}

void TcpServer::onNewConnection()
{
    qDebug() << "New socket connected";
    socket_ = server_.nextPendingConnection();
    ipAddress_ = socket_->peerAddress();
    connect(socket_, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
}

void TcpServer::onReadyRead()
{
    qDebug() << "Received new message";
    const auto message = socket_->readAll();
    messages_.append(message);
    qDebug() << QString(message);
    emit sendToQml("[" + ipAddress_.toString() + "] " + message);
}
