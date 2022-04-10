import QtQuick 2.15
import components 1.0
import assets 1.0

Item {
    property alias commandList: commandRepeater.model

    Rectangle {
        anchors.fill: parent
        color: Style.colourCommandBarBackground

        Row {
            anchors {
                top: parent.top
                bottom: parent.bottom
                right: parent.right
            }

            Repeater {
                id: commandRepeater
                Item {
                    width: Style.widthCommandButton
                    height: Style.heightCommandButton

                    Rectangle {
                        id: background
                        anchors.fill: parent
                        color: Style.colourCommandBarBackground

                        Rectangle {
                            id: textIcon
                            anchors {
                                centerIn: parent
                                verticalCenterOffset: -10
                            }
                            width: Style.widthCommandButton / 2
                            height: width
                            color: "transparent"
//                            color: modelData.ui_canExecute ? Style.colourCommandBarFont : Style.colourCommandBarFontDisabled
                            Image {
                                anchors.fill: parent
                                source: modelData.ui_icon
                                horizontalAlignment: Image.AlignHCenter
                            }
                        }

                        Text {
                            id: textDescription
                            anchors {
                                top: textIcon.bottom
                                bottom: parent.bottom
                                left: parent.left
                                right: parent.right
                            }
                            font.pixelSize: Style.pixelSizeNavigationBarText
                            color: modelData.ui_canExecute ? Style.colourCommandBarFont : Style.colourCommandBarFontDisabled
                            text: modelData.ui_description
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            hoverEnabled: true
                            onEntered: background.state = "hover"
                            onExited: background.state = ""
                            onClicked: if(modelData.ui_canExecute) {
                                           modelData.executed();
                                       }
                        }

                        states: [
                            State {
                                name: "hover"
                                PropertyChanges {
                                    target: background
                                    color: Qt.darker(Style.colourCommandBarBackground)
                                }
                            }
                        ]
                    }
                }
            }
        }
    }
}
