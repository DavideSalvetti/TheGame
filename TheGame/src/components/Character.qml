import QtQuick 2.15
import assets 1.0
import com.thegame.character 1.0

Item {

    property Character character

    width: parent.width
    height: parent.height

    Rectangle {
        id: container
        anchors {
            fill: parent
            margins: 5
        }
        color: "transparent"


        Image {
            id: characterImage
            source: character.imageSrc
            anchors.fill: parent
        }

        Text {
            id: lifepoints
            anchors {
                right: parent.right
                top: parent.top
            }

            text: character.lifePoints
            color: Style.colourCommandBarFont

        }

        Rectangle {
            width: 10
            height: 10
            radius: 5
            color: character.owner === 1 ? "red" : "blue"
        }
    }

    Behavior on x {
        NumberAnimation {duration: 200; easing.type: Easing.OutQuad }
    }

    Behavior on y {
        NumberAnimation {duration: 200; easing.type: Easing.OutQuad }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            game.characterClicked(character)
        }
    }
}
