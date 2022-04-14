import QtQuick 2.15
import assets 1.0
import com.thegame.character 1.0

Item {

    property Character character

    width: parent.width
    height: parent.height

    Rectangle {
        id: container
        width: parent.width - 8
        height: parent.height - 8
        anchors.centerIn: parent
        color: "transparent"

        Image {
            id: characterImage
            source: character != null ? character.imageSrc : ""
            anchors {
                top: parent.top
                bottom: rectLifePoints.top
            }

            width: parent.width
        }

        Text {
            id: lifepoints
            anchors {
                right: parent.right
                top: parent.top
            }

            text: character != null ? character.lifePoints : ""
            color: Style.colourCommandBarFont

        }

        Rectangle {
            id: rectLifePoints
            height: 5
            width: parent.width
            color: getPlayerColor()
            anchors.bottom: parent.bottom

            function getPlayerColor() {

                if (character != null) {
                    if (character.owner == 0)
                        return "gray"
                    else if (character.owner == 1)
                        return "red"
                    else if (character.owner == 2)
                        return "blue"
                }

                return "white"
            }
        }
    }
}
