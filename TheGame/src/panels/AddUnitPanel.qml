import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import components 1.0


Popup {
    id: popup

    property int starAvailable: 0

    parent: Overlay.overlay


    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)
    width: parent.width / 3 * 2
    height: columnId.implicitHeight + 30

    contentItem:  Column {
        width: parent.width
        id: columnId
        spacing: 10
        Label {
            text: qsTr("Click on the unit you want to add:")
            font {
                bold: true
                pointSize: 12
            }
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            id: characterRow
            spacing: 10
            property int itemSelected: -1
            anchors.horizontalCenter: parent.horizontalCenter

            ListModel {
                id: imgModel
                ListElement {img: "qrc:/img/swordsman.png"; star: 2; index: 1}
                ListElement {img: "qrc:/img/bow.png"; star: 2; index: 2}
                ListElement {img: "qrc:/img/wizard.png"; star: 4; index: 3}
                ListElement {img: "qrc:/img/knight.png"; star: 5; index: 4}
                ListElement {img: "qrc:/img/ninja.png"; star: 6; index: 5}
            }



            Repeater {
                model: imgModel


                delegate: Rectangle {
                    id: card
                    width: 64
                    height: 88
                    radius: 10

                    border {
                        width: characterRow.itemSelected == index ? 4 : 3
                        color: characterRow.itemSelected == index ? "blue" : "gray"
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

                    ColorOverlay {
                        anchors.fill: principalImage
                        source: principalImage
                        color: "#AA000000"
                        visible: starAvailable < star
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
                            if (starAvailable >= star)
                                characterRow.itemSelected = index
                            else
                                characterRow.itemSelected = -1
                        }
                    }

                }

            }
        }


        Button {
            id: control
            text: qsTr("Add Unit")
            enabled: characterRow.itemSelected != -1
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                if (characterRow.itemSelected != -1) {
                    game.addUnit(characterRow.itemSelected)
                    characterRow.itemSelected = -1
                    close()
                }
            }

            onHoveredChanged: {
                if (hovered) {
                    font.pointSize = 10
                } else {
                    font.pointSize = 8
                }
            }

            contentItem: Text {
                text: control.text
                font: control.font
                opacity: enabled ? 1.0 : 0.3
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                color: "blue"
                radius: 5
            }
        }

    }



    background: Rectangle {
        radius: 10
    }
}
