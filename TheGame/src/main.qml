import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 600
    height: 600
    visible: true
    title: qsTr("The Game")

    Row {
        id: header
        height: 40
        anchors.top: parent.top

        Label {
            id: round
            text: qsTr("Round") + ": " + game.roundNum
        }

        Label {
            id: player
            text: qsTr("Player") + ": " + game.roundPlayer
        }
    }

    Flickable {
        anchors {
            top: header.bottom
            bottom: footer.top
            left: parent.left
            right: parent.right
            leftMargin: (parent.width - grid.width) / 2
        }

        contentHeight: grid.height
        contentWidth: grid.width
        Grid {
            id: grid

            columns: 8
            Repeater {
                model: game.map_ui.tiles
                Rectangle {
                    width: 64
                    height: 64
                    border.color: "black"
                    border.width: 1

                    Rectangle {
                        width: parent.width - 8
                        height: parent.height - 8
                        anchors.centerIn: parent

                        visible: model.character != null
                        Image {
                            id: characterImage
                            source: model.character != null ?
                                        model.character.imageSrc : "";
                            anchors {
                                top: parent.top
                                bottom: rectOwner.top
                                left: parent.left
                                right: parent.right
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    game.setSelectedEntity(model.character)
                                }
                            }

                        }

                        Rectangle {
                            id: rectOwner
                            height: 5
                            width: parent.width
                            color: getPlayerColor()
                            anchors.bottom: parent.bottom

                            function getPlayerColor() {

                                if (model.character != null) {
                                    if (model.character.owner == 0)
                                        return "gray"
                                    else if (model.character.owner == 1)
                                        return "red"
                                    else if (model.character.owner == 2)
                                        return "blue"
                                }

                                return "white"
                            }
                        }
                    }

                }
            }
        }
    }

    Row {
        id: footer
        height: 40;
        anchors.bottom: parent.bottom


    }
}
