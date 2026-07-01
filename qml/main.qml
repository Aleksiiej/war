import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
    
    property var server: null
    property var client: null

    Rectangle
    {
        id: statusBarRect
        height: 28
        color: "lightblue"
        anchors
        {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        RowLayout
        {
            id: statusBar

            anchors.fill: parent

            Button
            {
                id: createServerButton
                text: "Create Server"
                onClicked:
                {
                    if(!server)
                    {
                        var serverComponent = Qt.createComponent("TcpServer.qml")
                        if(serverComponent.status === Component.Ready)
                        {
                            server = serverComponent.createObject(root)
                            server.username_ = usernameTextArea.text
                            chatListModel.append({message: "Server initialized. Listening..."})

                        }
                    }
                    else
                    {
                        chatListModel.append({message: "Instance of server already exists"})
                    }
                }
            }

            Rectangle
            {
                id: usernameRect
                height: parent.height
                width: 300
            
                TextArea
                {
                    id: usernameTextArea
                    anchors.fill: parent
                    placeholderText: qsTr("Enter username")
                    placeholderTextColor: "black"
                    color: "black"
                }
            }


            Rectangle
            {
                id: serverAddressRect
                height: parent.height
                width: 300
            
                TextArea
                {
                    id: serverAddressTextArea
                    anchors.fill: parent
                    placeholderText: qsTr("Enter IP address")
                    placeholderTextColor: "black"
                    color: "black"
                }
            }

            Button
            {
                id: joinServerButton
                text: "Join Server"
                onClicked:
                {
                    var clientComponent = Qt.createComponent("Client.qml")
                    if(clientComponent.status === Component.Ready)
                    {
                        client = clientComponent.createObject(root)
                        client.username_ = usernameTextArea.text
                        client.connectToServer("127.0.0.1", 12345)
                    }
                }
            }
        }
    }
 
    Rectangle
    {
        id: chatRect
        color: "lightblue"

        anchors
        {
            top: statusBarRect.bottom
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
                    if(server)
                    {
                        server.sendMessage(server.username_ + ": " + textArea1.text)
                    }
                    else if(client)
                    {
                        client.sendMessage(textArea1.text)
                    }
                    else
                    {
                        console.log("cannot send message, there is no server nor client");
                    }
                    textArea1.clear()
                }
                onPressed: parent.color = "lightgrey"
                onReleased: parent.color = "gray"
            }
        }
    }
}