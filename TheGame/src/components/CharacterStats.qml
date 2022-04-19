import QtQuick 2.15
import components 1.0
import com.thegame.character 1.0

Item {
    property Character character

    visible: character != null

    Row {
        anchors.fill: parent

        spacing: 10

        Image {
            width: parent.height
            height: width

            source: character == null ? "" : character.imageSrc
        }

        RectangleStat {
            anchors {
                top: parent.top
                bottom: parent.bottom
                topMargin: 10
                bottomMargin: 10
            }

            width: 24

            colorRect: character == null ? "red" : (character.owner == 1 ?
                                                        "red" : "blue")
            imageSource: "qrc:/img/heart_2.png"
            value: character == null ? 0 : character.lifePoints
            maxValue: character == null ? 0 : character.maxLifePoints
        }

        RectangleStat {
            anchors {
                top: parent.top
                bottom: parent.bottom
                topMargin: 10
                bottomMargin: 10
            }

            width: 24

            colorRect: character == null ? "red" : (character.owner == 1 ?
                                                        "red" : "blue")
            imageSource: "qrc:/img/sword.png"
            value: character == null ? 0 : character.attackPoints
            maxValue: 10
        }

        RectangleStat {
            anchors {
                top: parent.top
                bottom: parent.bottom
                topMargin: 10
                bottomMargin: 10
            }

            width: 24

            colorRect: character == null ? "red" : (character.owner == 1 ?
                                                        "red" : "blue")
            imageSource: "qrc:/img/game.png"
            value: character == null ? 0 : character.defPoints
            maxValue: 4
        }
    }
}
