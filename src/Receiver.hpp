#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QtQml>

class Receiver: public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    Receiver();

    Q_INVOKABLE void addMessage(const QString& msg);
    Q_INVOKABLE QString& getLastMessage();

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer server_{};
    QTcpSocket* socket_{};
    QVector<QString> messages_{};
};