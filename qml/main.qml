import QtQuick
import QtQuick.Controls


Window 
{
    id: root
    visible: true
    color: "lightblue"

    width: 800
    height: 600
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height

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
            
            MouseArea
            {
                id: mouseArea1
                anchors.fill: parent
                onClicked: 
                {
                    console.log("HELLO");
                }
                onPressed: parent.color = "lightgrey"
                onReleased: parent.color = "gray"
            }
        }
    }
}