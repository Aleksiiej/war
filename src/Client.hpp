#include <QTcpSocket>
#include <QObject>
#include <QtQml>

#include <iostream>

class Client: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString username_ READ getUsername WRITE setUsername)

public:
    Client();
    ~Client();
    
    Q_INVOKABLE void connectToServer(QString address);
    Q_INVOKABLE void sendMessage(const QString& message);
    Q_INVOKABLE const QString& getUsername();
    Q_INVOKABLE void setUsername(const QString& username);

private slots:
    void onDisconnected();
    void onErrorOccurred();
    void onReadyRead();

signals:
    void sendToQml(const QString& msg);

private:
    QTcpSocket socket_{};
    QString username_;
};