import QtQuick 2.15
import assets 1.0
import com.thegame.command 1.0

Item {
    property Command command
    width: command.ui_canExecute ? Style.widthCommandButton : 0
    height: Style.heightCommandButton

    visible: command.ui_canExecute

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.colourCommandBarBackground
        radius: 5

        Rectangle {
            id: textIcon
            anchors {
                centerIn: parent
                verticalCenterOffset: -10
            }
            width: Style.widthCommandButton / 2 + 10
            height: width
            color: "transparent"
            border {
                width: 1
                color: "white"
            }

            radius: 30

            Image {
                anchors.fill: parent
                anchors.margins: Style.iconMargins
                source: command.ui_icon
                horizontalAlignment: Image.AlignHCenter
            }
        }

        Text {
            id: textDescription
            anchors {
                top: textIcon.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            font.pixelSize: Style.pixelSizeNavigationBarText
            color: command.ui_canExecute ? Style.colourCommandBarFont : Style.colourCommandBarFontDisabled
            text: command.ui_description
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: if(command.ui_canExecute) {
                           command.executed();
                       }
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: Style.colourCommandBarHovered
                }
            }
        ]
    }
}
