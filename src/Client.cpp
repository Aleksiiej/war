#include "Client.hpp"

Client::Client()
{
    qDebug() << "Client initialized.";
    connect(&socket_, &QTcpSocket::connected, this, &Client::onConnected);
    connect(&socket_, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);
}

void Client::connectToServer(const QString& host, const int port)
{
    socket_.connectToHost(host, port);
    qDebug() << "Connecting to server at " + host + ":" + QString::number(port);
    if (socket_.waitForConnected(3000))
    {
        qDebug() << "Connection succes";
    }
    else
    {
        qDebug() << "Connection failed";
    }
}

void Client::sendMessage(const QString& message)
{
    socket_.write((username_ + ": " + message).toUtf8());
    socket_.flush();
    qDebug() << "Data written to socket by sender";
}

const QString& Client::getUsername()
{
    return username_;
}

void Client::setUsername(const QString& username)
{
    username_ = username;
}

void Client::onConnected()
{
    qDebug() << "Socket connected";
}

void Client::onErrorOccurred()
{
    qDebug() << "Error during socket connection";
}

void Client::onReadyRead()
{
    emit sendToQml(socket_.readAll());
}