#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include <QObject>
#include <QtQml>

class TcpServer: public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    TcpServer();

    Q_INVOKABLE void addMessage(const QString& msg);
    Q_INVOKABLE void sendMessage(const QString& message);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

signals:
    void sendToQml(const QString& msg);

private:
    QTcpServer server_{};
    QHash<QHostAddress, QTcpSocket*> sockets_;
    QVector<QString> messages_{};
};