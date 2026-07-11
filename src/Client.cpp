#include "Client.hpp"

Client::Client()
{
    connect(&socket_, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(&socket_, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);
    connect(&socket_, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

Client::~Client()
{
    socket_.disconnectFromHost();
}

bool Client::connectToServer(QString address)
{
    const auto addressList = address.split(':');
    if(addressList.size() != 2)
    {
        sendToQml("Incorrect format of server address");
        return false;
    }
    const auto host = addressList.at(0);
    const auto port = addressList.at(1).toUShort();
    socket_.connectToHost(host, port);
    emit sendToQml("Connecting to server at " + host + ":" + QString::number(port));
    if (socket_.waitForConnected(3000))
    {
        emit sendToQml("Connection succes");
        return true;
    }
    else
    {
        emit sendToQml("Connection failed");
        return false;
    }
}

void Client::sendMessage(const QString& message)
{
    socket_.write((username_ + ": " + message).toUtf8());
    socket_.flush();
}

const QString& Client::getUsername()
{
    return username_;
}

void Client::setUsername(const QString& username)
{
    username_ = username;
}

void Client::onDisconnected()
{
    emit sendToQml("Disconnected from server");
}

void Client::onErrorOccurred()
{
    emit sendToQml("Error during connection");
}

void Client::onReadyRead()
{
    const auto message = socket_.readAll();
    emit sendToQml(message);
}