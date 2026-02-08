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
    
    QTcpSocket* socket_{};
    std::shared_ptr<QTcpServer> server_{};

signals:
    void dummySignal();

public slots:
    void dummySlot()
    {
        std::cout << "dummy slot speaking" << std::endl;
    }

    void onNewConnection()
    {
        std::cout << "New connection avalaible" << std::endl;
        socket_ = server_->nextPendingConnection();
        char buf[1024];
        qint64 lineLength = socket_->readLine(buf, sizeof(buf));
        for(int i = 0; i < lineLength; i++)
        {
            std::cout << buf[i];
        }
    }
};