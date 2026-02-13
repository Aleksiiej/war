#include <QObject>
#include <QVector>

class ChatContainer: public QObject
{
    Q_OBJECT

public:
    void addMessage(const QString& msg);
private:
    QVector<QString> messages{};
};