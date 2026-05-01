import QtQuick 2.0

Rectangle
{
    id: commonButton

    width: buttonText.width + paddingHorizontal * 2
    height: buttonText.height + paddingVertical * 2

    color: "#e9e9e9"
    radius: 10

    property int paddingHorizontal: 10
    property int paddingVertical: 5

    property alias text: buttonText.text

    signal clicked

    Text
    {
        id: buttonText
        anchors.centerIn: parent
        font.pixelSize: 18
        color: "black"
    }

    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: commonButton.clicked()
        onPressed: commonButton.opacity = 0.5
        onReleased: commonButton.opacity = 1
    }
}