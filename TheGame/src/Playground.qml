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

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            game.tileClicked(modelData)
                        }
                    }
                }
            }

            Repeater {
                model: game.charactersList
                delegate: Character {


                    height: grid.width / 8
                    width: height

                    x: (modelData.xPos) * width
                    y: (modelData.yPos) * height

                    character: modelData
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
