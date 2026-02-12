#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <iostream>

class NetworkManager: public QObject
{
    Q_OBJECT

public:
    NetworkManager();

    void connectToServer(const QString& host, const int port);
    void sendMessage(QString&& message);
    
    QTcpSocket* socket_{};
    QTcpSocket 
    QTcpServer server_{};

public slots:
    void onReadyRead()
    {
        std::cout << "Received new message" << std::endl;
        QDataStream in(socket_);
        QString message;
        in >> message;
        qDebug() << "Received:" << message;
    }

    void onNewConnection()
    {
        std::cout << "New socket connected" << std::endl;
        socket_ = server_.nextPendingConnection();
    }
};