#include "Sender.hpp"

Sender::Sender()
{
    qDebug() << "Sender initialized.";
    connect(&socket_, &QTcpSocket::connected, this, &Sender::onConnected);
    connect(&socket_, &QTcpSocket::errorOccurred, this, &Sender::onErrorOccurred);
}

void Sender::connectToServer(const QString& host, const int port)
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

void Sender::sendMessage(const QString& message)
{
    socket_.write(message.toUtf8());
    socket_.flush();
    qDebug() << "Data written to socket by sender";
}

void Sender::onConnected()
{
    qDebug() << "Socket connected";
}

void Sender::onErrorOccurred()
{
    qDebug() << "Error during socket connection";
}