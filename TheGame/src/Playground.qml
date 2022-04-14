import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import components 1.0
import assets 1.0


Item {

    Header {
        id: header
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        height: Style.heightHeader
    }

    Flickable {
        anchors {
            top: header.bottom
            bottom: commandBar.top
            left: parent.left
            right: parent.right
            topMargin: 10
            leftMargin: (parent.width - grid.width) / 2
        }

        clip: true
        contentHeight: grid.height
        contentWidth: grid.width
        Grid {
            id: grid

            columns: 8
            rows: 8
            Repeater {
                model: game.map_ui.tiles

                Rectangle {
                    width: 64
                    height: 64
                    border.color: "black"
                    border.width: 1
                    color: getGroundColor()

                    function getGroundColor() {
                        if (model.free) return "blue"
                        else if (model.underAttack) return "red"

                        return "green"
                    }

                    Image {
                        anchors.fill: parent
                        anchors.margins: 8
                        visible: solid
                        source: "qrc:/img/mountain.png"
                    }

                    Character {
                        visible: model.character !== null
                        character: model.character
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            game.tileClicked(modelData)
                        }
                    }

                }
            }

            Repeater {
                model: game.characters
                delegate: Item {


                    height: grid.width / 8
                    width: height

                    x: (model.xPos - 1) * width
                    y: (model.yPos - 1) * height

                    Rectangle {
                        id: container
                        anchors {
                            fill: parent
                            margins: 5
                        }
                        color: "transparent"

                        Text {
                            id: lifepoints
                            anchors {
                                right: parent.right
                                top: parent.top
                            }

                            text: lifePoints
                            color: Style.colourCommandBarFont

                        }

                        Rectangle {
                            width: 10
                            height: 10
                            radius: 5
                            color: owner === 1 ? "red" : "blue"
                        }

                        Image {
                            id: characterImage
                            source: imageSrc
                            anchors.fill: parent


                        }
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            game.characterClicked(model.xPos, model.yPos)
                        }
                    }
                }
            }

        }
    }

    CommandBar {
        id: commandBar

        anchors {
            left: parent.left
            bottom: parent.bottom
            right: parent.right
        }
        height: Style.heightCommandBar

        commandList: game.commandBar
    }
}
