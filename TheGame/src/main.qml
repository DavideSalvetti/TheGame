import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Flickable {
        anchors.fill: parent
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

                    Image {
                        id: characterImage
                        source: model.character != null ?
                                    model.character.imageSrc : "";
                        anchors.fill: parent

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {

                            }
                        }

                    }
                }
            }
        }

    }
}
