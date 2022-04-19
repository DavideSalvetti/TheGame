import QtQuick 2.15
import components 1.0
import assets 1.0

Item {
    property alias commandList: commandRepeater.model

    Rectangle {
        anchors.fill: parent
        color: Style.colourCommandBarBackground

        Rectangle {
            id: line
            height: 1
            width: parent.width
            anchors.top: parent.top
            color: Style.colourCommandBarFont
        }

        Rectangle {
            anchors {
                top: parent.top
                topMargin: 2
                bottom: parent.bottom
                left: parent.left
            }

            width: parent.width / 2

            visible: game.selectedCharacter != null

            CharacterStats {
                anchors.fill: parent
                character: game.selectedCharacter
            }

            color: Style.colourCommandBarBackground
        }

        Row {
            anchors {
                top: parent.top
                topMargin: 2
                bottom: parent.bottom
                right: parent.right
            }

            width: parent.width / 2

            layoutDirection: Qt.RightToLeft

            Repeater {
                id: commandRepeater
                CommandButton {
                    command: modelData
                }
            }
        }
    }
}
