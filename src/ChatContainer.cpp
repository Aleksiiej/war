#include "ChatContainer.hpp"

void ChatContainer::addMessage(const QString& msg)
{
    messages.append(msg);
}