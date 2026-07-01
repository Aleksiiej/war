import war 1.0

Client
{
    onSendToQml: (msg) =>
    {
        chatListModel.append({message: msg})
    }
}