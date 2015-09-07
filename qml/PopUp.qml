import QtQuick 2.0
import QmlGraphs 1.0

Item {
    property alias text: label.text

    width: bg.width
    height: bg.height

    Rectangle {
        id: bg
        color: Style.POPUP_BGCOLOR
        opacity: 0.5
        radius: 3

        width: label.width + 10
        height: label.height + 10
    }

    Text {
        id: label
        color: Style.POPUP_TEXTCOLOR
        font.bold: Style.POPUP_BOLD
        font.pixelSize: Style.POPUP_PIXELSIZE
        anchors.centerIn: bg
    }
}

