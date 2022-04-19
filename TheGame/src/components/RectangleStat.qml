import QtQuick 2.15

Item {

    property alias imageSource : image.source
    property int maxValue : 15
    property int value : 0
    property alias colorRect: propertyRect.color

    Rectangle {
        id: container
        border {
            width: 1
            color: "white"
        }
        color: "black"

        anchors.top: parent.top
        anchors.bottom: image.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: 10

        radius: 4

        Rectangle {
            id: propertyRect
            radius: 3
            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                margins: 1
            }

            height: (value * parent.height / maxValue) - 2

            color: "red"
        }
    }

    Image {
        id: image
        height: 24
        width: 24

        anchors.bottom: parent.bottom
    }
}
