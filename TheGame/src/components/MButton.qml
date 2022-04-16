import QtQuick 2.15
import QtQuick.Controls 2. 15


Button {
    id: control

    Behavior on font.pointSize {

        NumberAnimation {
            target: control
            property: "font.pointSize"
            duration: 100
            easing.type: Easing.Linear
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
        gradient: Gradient.CrystalRiver
        radius: 5
    }
}
