import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import components 1.0
import assets 1.0


Item {


    Connections {
        target: game

        function onGameFinished(winner) {
            winnerRect.visible = true

            if (winner === 1) {
                labelWinner.text = "Player 1"
                winnerInternRect.gradient = Gradient.LoveKiss
            } else {
                labelWinner.text = "Player 2"
                winnerInternRect.gradient = Gradient.FlyHigh
            }

            showWinnerRect.running = true
        }
    }


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

            columns: game.map_ui.mapHeight
            rows: game.map_ui.mapWidth
            Repeater {
                model: game.map_ui.tiles

                Rectangle {
                    width: game.map_ui.tileWidth
                    height: game.map_ui.tileHeight
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
                model: game.map_ui.charactersList
                delegate: Character {


                    height: grid.width / game.map_ui.mapWidth
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


    Rectangle {
        id: winnerRect
        anchors.fill: parent
        visible: false
        color: "black"
        opacity: 0

        SequentialAnimation {
            id: showWinnerRect
            NumberAnimation { target: winnerRect; property: "opacity"; from: 0; to: 0.7; duration: 3000}
            NumberAnimation {
                target: labelWinner;
                property: "x";
                from: - 100; to: winnerRect.width/2 - labelWinner.width/2;
                duration: 500;
                easing.type: Easing.OutBounce
            }
        }

        Rectangle {
            id: winnerInternRect
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            height: parent.height / 4

            Label {
                text: qsTr("The winner is:")
                color: "white"
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                font {
                    pointSize: 24
                    bold: true
                    italic: true
                }
            }

            Label {
                id: labelWinner
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
                font {
                    pointSize: 24
                    bold: true
                    italic: true
                }

                opacity: 1

                x: -200
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("MouseArea clicked")
                stack.pop()
            }
        }
    }
}
