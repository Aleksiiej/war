#include <QTcpSocket>
#include <QObject>

#include <iostream>

class Client: public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    Client();
    
    void connectToServer(const QString& host, const int port);
    void sendMessage(const QString& message);

private slots:
    void onConnected();
    void onErrorOccurred();

private:
    QTcpSocket socket_{};
};