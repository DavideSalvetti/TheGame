import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import components 1.0
import assets 1.0


Window {
    width: 700
    height: 700
    visible: true
    title: qsTr("The Game")

    color: Style.colourBackground

    Connections {
        target: game

        function onGameFinished(winner) {
            console.log("The winner is:" + winner)
        }
    }

    StackView {
        id: stack
        initialItem: view
        anchors.fill: parent

        Component {
            id: view

            Rectangle {
                id: backgroundRectangle
                anchors.fill: parent


                Image {
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/img/mountain.png"
                    height: 512
                    width: 512
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 10
                    Label {
                        text: qsTr("Choose a map:")
                    }

                    Row {
                        spacing: 10
                        Button {
                            text: qsTr("Small (8x8)")
                        }

                        Button {
                            text: qsTr("Medium (12x12)")
                        }

                        Button {
                            text: qsTr("Large (16x16)")
                        }
                    }
                }

                MouseArea {

                    anchors.fill: parent
                    Text {
                        text: stack.depth
                        color: "white"
                        anchors.fill: parent
                    }
                    onClicked:  {
                        console.log("Qml CLicked")
                        stack.push("qrc:/Playground.qml")
                    }
                }
            }


        }
    }
}
