#include <QTcpSocket>
#include <QObject>

#include <iostream>

class Sender: public QObject
{
    Q_OBJECT

public:
    Sender();
    void connectToServer(const QString& host, const int port);
    void sendMessage(const QString& message);

private slots:
    void onConnected();
    void onErrorOccurred();

private:
    QTcpSocket socket_{};
};