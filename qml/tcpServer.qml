import QtQuick
import QtQuick.Controls

import war 1.0


Window 
{
    id: root
    visible: true

    width: 800
    height: 600
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    
    Rectangle
    {
        id: chatRect
        color: "lightblue"

        anchors
        {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: rect1.top
        }
        
        ListView
        {
            id: chatListView
            anchors.fill: parent
            model: ListModel{
                id: chatListModel
                ListElement{message: "Hi!"}
            }
            delegate: Text{
                text: message
            }
            clip: true
        }
    }

    Rectangle
    {
        id: rect1
        height: 30
        anchors
        {
            left: parent.left
            bottom: parent.bottom
            right: parent.right
        }

        property int buttonWidth: 60

        TextArea
        {
            id: textArea1
            height: parent.height
            width: parent.width - parent.buttonWidth
            anchors
            {
                bottom: parent.bottom
                left: parent.left
            }
            placeholderText: qsTr("Enter text here")
            placeholderTextColor: "black"
            color: "black"
            focus: true
        }

        Rectangle
        {
            height: parent.height
            width: parent.buttonWidth
            anchors
            {
                bottom: parent.bottom
                right: parent.right
            }
            color:"gray"

            Text
            {
                anchors.centerIn: parent
                text: "Send"
            }
            
            MouseArea
            {
                id: mouseArea1
                anchors.fill: parent
                onClicked: 
                {
                    chatListModel.append({message: textArea1.text})
                    tcpServer.sendMessage(textArea1.text)
                    textArea1.clear()
                }
                onPressed: parent.color = "lightgrey"
                onReleased: parent.color = "gray"
            }
        }
    }

    TcpServer
    {
        id: tcpServer
        onSendToQml:
        {
            chatListModel.append({message: msg})
        }
    }
}