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

    Item
    {
        id: ui
        anchors.fill: parent
        state: "disconnected"

        states: [
            State
            {
                name: "disconnected"
                PropertyChanges {target: usernameRect; color: "white"}
                PropertyChanges {target: usernameTextArea;
                                 placeholderText: "Enter username";
                                 enabled: true}
                PropertyChanges {target: serverAddressRect; color: "white"}
                PropertyChanges {target: serverAddressTextArea; enabled: true}
                PropertyChanges {target: createServerButton; text: "Create Server"}
                PropertyChanges {target: joinServerButton; enabled: true}
                PropertyChanges {target: sendMsgMouseArea; enabled: false}
            },
            State
            {
                name: "server"
                PropertyChanges {target: usernameRect; color: "lightgrey"}
                PropertyChanges {target: usernameTextArea;
                                 placeholderText: server.username_;
                                 enabled: false}
                PropertyChanges {target: serverAddressRect; color: "lightgrey"}
                PropertyChanges {target: serverAddressTextArea; enabled: false}
                PropertyChanges {target: createServerButton; text: "Close server"}
                PropertyChanges {target: joinServerButton; enabled: false}
                PropertyChanges {target: sendMsgMouseArea; enabled: true}
            },
            State
            {
                name: "client"
                PropertyChanges {target: usernameRect; color: "lightgrey"}
                PropertyChanges {target: usernameTextArea;
                                 placeholderText: client.username_;
                                 enabled: false}
                PropertyChanges {target: serverAddressRect; color: "lightgrey"}
                PropertyChanges {target: serverAddressTextArea; enabled: false}
                PropertyChanges {target: createServerButton; enabled: false}
                PropertyChanges {target: joinServerButton; text: "Disconnect"}
                PropertyChanges {target: sendMsgMouseArea; enabled: true}
            }
        ]
    
    
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
                                ui.state = "server"
                                chatListModel.append({message: "Server created. Listening..."})
                            }
                        }
                        else
                        {
                            server.destroy()
                            ui.state = "disconnected"
                            chatListModel.append({message: "Server removed"})
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
                        placeholderText: qsTr("Enter IP address and port")
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
                        if(!client)
                        {
                            var clientComponent = Qt.createComponent("Client.qml")
                            if(clientComponent.status === Component.Ready)
                            {
                                client = clientComponent.createObject(root)
                                client.username_ = usernameTextArea.text
                                client.connectToServer(serverAddressTextArea.text)
                                ui.state = "client"
                            }
                        }
                        else
                        {
                            client.destroy()
                            ui.state = "disconnected"
                            chatListModel.append({message: "Disconnected from server"})
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
                bottom: sendMsgRect.top
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
            id: sendMsgRect
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
                id: sendMsgTextArea
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
                    id: sendMsgMouseArea
                    anchors.fill: parent
                    enabled: false
                    onClicked: 
                    {
                        if(server)
                        {
                            server.sendMessage(server.username_ + ": " + sendMsgTextArea.text)
                        }
                        else if(client)
                        {
                            client.sendMessage(sendMsgTextArea.text)
                        }
                        sendMsgTextArea.clear()
                    }
                    onPressed: parent.color = "lightgrey"
                    onReleased: parent.color = "gray"
                }
            }
        }
    }
}   