pragma Singleton
import QtQuick 2.15

Item {
    readonly property color colourBackground: "#000000"

    readonly property color colourPlayer1: "red"
    readonly property color colourPlayer2: "blue"


    readonly property int pixelSizeNavigationBarText: 12


    readonly property color colourHeaderFont: "#ffffff"
    readonly property real heightHeader: 40

    readonly property color colourCommandBarBackground: "#000000"
    readonly property color colourCommandBarFont: "#ffffff"
    readonly property color colourCommandBarFontDisabled: "#636363"
    readonly property color colourCommandBarHovered: "#333333"
    readonly property real heightCommandBar: heightCommandButton


    readonly property real widthCommandButton: 80
    readonly property real heightCommandButton: widthCommandButton
    readonly property real iconMargins: 5

}
