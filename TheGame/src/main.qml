import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Grid {
        anchors.fill: parent
        columns: 8
        Repeater {
                model: game.map_ui.tiles
            Rectangle {
                width: 20
                height: 20
                border.color: "black"
                border.width: 1
            }
        }
    }
}
