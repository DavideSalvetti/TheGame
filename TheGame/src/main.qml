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

    StackView {
        id: stack
        initialItem: view
        anchors.fill: parent

        Component {
            id: view

            Rectangle {
                id: backgroundRectangle
                anchors.fill: parent


                Rectangle {
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        right: parent.right
                    }

                    height: parent.width / 3
                    color:  "#00FF00"
                }

                Rectangle {
                    anchors {
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }

                    height: parent.width / 3 * 2
                    gradient: Gradient.LightBlue
                }


                Image {
                    id: sun
                    anchors {
                        top: parent.top
                        right: parent.right
                        margins: 10
                    }

                    width: 80
                    height: 80

                    source: "qrc:/img/sun.png"


                    RotationAnimator {
                        target: sun
                        from: 0
                        to: 360
                        duration: 5000
                        running: true
                        loops: Animation.Infinite
                    }
                }


                Image {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: - 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/img/mountain.png"
                    height: 512
                    width: 512
                }

                Image {
                    id: swordsman
                    x: 0
                    y: parent.height - height

                    width: 64
                    height: 64

                    source: "qrc:/img/swordsman.png"
                }


                Rectangle {
                    anchors {
                        top: parent.top
                        left: parent.left
                        right: parent.right
                        topMargin: 10
                        leftMargin: parent.width / 5
                        rightMargin: parent.width / 5
                    }

                    height: parent.height / 4

                    color: "#aaffffff"
                    radius: 10

                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width
                        spacing: 10

                        Label {
                            text: qsTr("Choose the size of the map:")
                            anchors.horizontalCenter: parent.horizontalCenter
                            font {
                                bold: true
                                pointSize: 16
                            }
                        }

                        Row {
                            spacing: 10
                            width: parent.width
                            anchors.horizontalCenter: parent.horizontalCenter
                            leftPadding: 5
                            MButton {

                                text: qsTr("Small (8x8)")
                                onClicked: {
                                    game.initGame(8, 8)
                                    stack.push("qrc:/Playground.qml")
                                }

                                width: parent.width / 3 - 10
                                font.bold: true
                            }

                            MButton {
                                text: qsTr("Medium (12x12)")
                                onClicked: {
                                    game.initGame(12, 12)
                                    stack.push("qrc:/Playground.qml")
                                }

                                width: parent.width / 3 - 10
                                font.bold: true
                            }

                            MButton {
                                text: qsTr("Large (16x16)")
                                onClicked: {
                                    game.initGame(16, 16)
                                    stack.push("qrc:/Playground.qml")
                                }

                                width: parent.width / 3 - 10
                                font.bold: true
                            }
                        }
                    }
                }
            }
        }
    }
}
