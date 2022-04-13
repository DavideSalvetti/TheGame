import QtQuick 2.15
import QtQuick.Controls 2.15
import assets 1.0

Item {


    Label {
        id: round
        anchors {
            left: parent.left
            top: parent.top
        }

        color: Style.colourHeaderFont
        font.bold: true
        font.pixelSize: 20

        height: parent.height
        verticalAlignment: "AlignVCenter"
        text: qsTr("Round") + ": " + game.roundNum
    }

    Label {
        id: player
        anchors {
            right: parent.right
            top: parent.top
        }

        color: game.roundPlayer == 1 ? Style.colourPlayer1 : Style.colourPlayer2
        font.bold: true
        font.pixelSize: 20

        height: parent.height
        verticalAlignment: "AlignVCenter"
        text: qsTr("Player") + ": " + game.roundPlayer
    }

    Rectangle {
        width: parent.width
        height: 1
        anchors.bottom: parent.bottom

        color: Style.colourCommandBarFont
    }
}
