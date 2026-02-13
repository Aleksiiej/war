#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

#include <iostream>

class Receiver: public QObject
{
    Q_OBJECT

public:
    Receiver();

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer server_{};
    QTcpSocket* socket_{};
};