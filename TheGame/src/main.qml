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

                Rectangle {
                    id: garden
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        right: parent.right
                    }

                    height: parent.height / 3
                    color:  "#00FF00"
                }

                Rectangle {
                    id: sky
                    anchors {
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }

                    height: parent.height / 3 * 2
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
                    id: mountain
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: - 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/img/mountain.png"
                    height: 512
                    width: 512

                    Image {
                        id: magician
                        anchors {
                            top: parent.top
                            horizontalCenter: parent.horizontalCenter
                            topMargin:  - 10
                        }

                        width: 128
                        height: 128

                        source: "qrc:/img/wizard.png"
                    }

                    Image {
                        id: ninja
                        anchors {
                            bottom: parent.bottom
                            horizontalCenter: parent.horizontalCenter
                            horizontalCenterOffset:  - 20
                            bottomMargin:  - 10
                        }

                        width: 128
                        height: 128
                        rotation: 20

                        source: "qrc:/img/ninja.png"
                    }
                }

                Image {
                    id: swordsman
                    anchors {
                        left: parent.left
                        bottom: sky.bottom
                        leftMargin: 10
                        bottomMargin:  - 10
                    }

                    width: 128
                    height: 128

                    source: "qrc:/img/swordsman.png"
                }

                Image {
                    id: archer
                    anchors {
                        right: parent.right
                        bottom: sky.bottom
                        rightMargin: 10
                        bottomMargin:  - 10
                    }

                    width: 128
                    height: 128

                    source: "qrc:/img/bow.png"
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

                    height: columnId.implicitHeight + 10

                    color: "#aaffffff"
                    radius: 10

                    Column {
                        id: columnId
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width
                        spacing: 5

                        Image {
                            y: -5
                            source: "qrc:/img/crown.png"
                            anchors.horizontalCenter: parent.horizontalCenter
                            height: 104
                            width: 104

                            Label {
                                text: "The Game"
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: -5
                                font {
                                    bold: true
                                    pointSize: 18
                                }
                            }
                        }

                        Label {
                            text: qsTr("Choose the size of the map:")
                            anchors.horizontalCenter: parent.horizontalCenter
                            font {
                                bold: false
                                pointSize: 10
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
