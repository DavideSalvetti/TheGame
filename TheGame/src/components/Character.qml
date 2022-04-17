import QtQuick 2.15
import assets 1.0
import com.thegame.character 1.0

Item {

    property Character character

    width: parent.width
    height: parent.height

    visible: character != null

    Rectangle {
        id: container
        anchors {
            fill: parent
            margins: 5
        }
        color: "transparent"


        Image {
            id: characterImage
            source: character == null ? "" : character.imageSrc
            anchors {
                top: parent.top
                bottom: parent.bottom
            }
            x: 0
            width: parent.width

        }

        Text {
            id: lifepoints

            property real previousText: 0

            anchors {
                right: parent.right
                top: parent.top
            }

            text: character == null ? 0 : character.lifePoints
            color: Style.colourCommandBarFont

            onTextChanged: {
                if (character != null) {
                    if (previousText > character.lifePoints) {
                        lifePointsAnimation.running = true
                    }

                    previousText = character.lifePoints
                }
            }

            Component.onCompleted: {
                previousText = character.lifePoints
            }
        }

        Rectangle {
            width: 10
            height: 10
            radius: 5
            color: (character == null ? "white" : (character.owner === 1 ? "red" : "blue"))
        }
    }

    Behavior on x {
        NumberAnimation {duration: 200; easing.type: Easing.OutQuad }
    }

    Behavior on y {
        NumberAnimation {duration: 200; easing.type: Easing.OutQuad }
    }

    SequentialAnimation {
        id: lifePointsAnimation
        NumberAnimation {target: characterImage; property: "x"; duration: 100; from: 0; to: 5}
        NumberAnimation {target: characterImage; property: "x"; duration: 100; from: 5; to: -5}
        NumberAnimation {target: characterImage; property: "x"; duration: 100; from: -5; to: 5}
        NumberAnimation {target: characterImage; property: "x"; duration: 100; from: 5; to: 0}
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            game.characterClicked(character)
        }
    }
}
