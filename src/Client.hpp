#include <QTcpSocket>
#include <QObject>
#include <QtQml>

#include <iostream>

class Client: public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    Client();
    
    Q_INVOKABLE void connectToServer(const QString& host, const int port);
    Q_INVOKABLE void sendMessage(const QString& message);

private slots:
    void onConnected();
    void onErrorOccurred();
    void onReadyRead();

signals:
    void sendToQml(const QString& msg);

private:
    QTcpSocket socket_{};
};