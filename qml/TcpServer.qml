import war 1.0

TcpServer
{
    onSendToQml: (msg) =>
    {
        chatListModel.append({message: msg})
    }
}