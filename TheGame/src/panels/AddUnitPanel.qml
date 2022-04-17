import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0


Popup {
    id: popup

    parent: Overlay.overlay


    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)
    width: parent.width / 2
    height: parent.height / 3

    contentItem: Rectangle {
        anchors {
            fill: parent
            margins: 10
        }

        Column {
            spacing: 10
            Label {
                text: qsTr("Click on the unit you want to add:")
                font {
                    bold: true
                    pointSize: 12
                }
            }

            Row {
                id: characterRow
                spacing: 10
                property int itemSelected: -1

                ListModel {
                    id: imgModel
                    ListElement {img: "qrc:/img/swordsman.png"; star: 2; index: 1}
                    ListElement {img: "qrc:/img/bow.png"; star: 2; index: 2}
                    ListElement {img: "qrc:/img/wizard.png"; star: 4; index: 3}
                }



                Repeater {
                    model: imgModel


                    delegate: Rectangle {
                        id: card
                        width: 64
                        height: 88
                        radius: 10

                        border {
                            width: 3
                            color: characterRow.itemSelected == index ? "#00ccff" : "gray"
                        }

                        Image {
                            id: principalImage
                            anchors {
                                top: parent.top
                                left: parent.left
                                right: parent.right
                            }
                            height: 64

                            source: img
                        }

                        Image {
                            anchors.top: principalImage.bottom
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: 24

                            source: "qrc:/img/favourite.png"

                            Text {
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                text: star
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                characterRow.itemSelected = index
                            }
                        }

                    }

                }
            }

        }
    }


    background: Rectangle {
        radius: 10
    }
}
