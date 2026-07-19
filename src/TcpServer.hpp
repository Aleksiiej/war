#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include <QObject>
#include <QtQml>

class TcpServer: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString username_ READ getUsername WRITE setUsername NOTIFY usernameChanged)

public:
    TcpServer();
    ~TcpServer();

    Q_INVOKABLE void addMessage(const QString& msg);
    Q_INVOKABLE void sendMessage(const QString& message);
    Q_INVOKABLE const QString& getUsername();
    Q_INVOKABLE void setUsername(const QString& username);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

signals:
    void usernameChanged();
    void sendToQml(const QString& msg);

private:
    QTcpServer server_{};
    QHash<QHostAddress, QTcpSocket*> sockets_;
    QVector<QString> messages_{};
    QString username_;
    const uint16_t port_{45678};
};