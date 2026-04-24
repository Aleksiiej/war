#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QtQml>

class TcpServer: public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    TcpServer();

    Q_INVOKABLE void addMessage(const QString& msg);
    Q_INVOKABLE QString& getLastMessage();
    Q_INVOKABLE void sendMessage(const QString& message);

private slots:
    void onNewConnection();
    void onReadyRead();

signals:
    void sendToQml(const QString& msg);

private:
    QTcpServer server_{};
    QTcpSocket* socket_{};
    QHostAddress ipAddress_{};
    QVector<QString> messages_{};
};