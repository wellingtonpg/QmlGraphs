import QtQuick 2.3
import QtQuick.Window 2.2
import QmlGraphs 1.0

Window {
    visible: true
    width: 400
    height: 400

    Pie {
        anchors.fill: parent
        anchors.margins: 10
        antialiasing: true
        showShadow: true
        showSeparator: true
        showCenterColor: true
        title: "My title"
        subtitle: "My subtitle"

        PieModel {
            Slice { label: "USA"; value: 50; color: "#5B90BF" }
            Slice { label: "UK"; value: 15; color: "#96B5B4" }
            Slice { label: "Brazil"; value: 5; color: "#A3BE8C" }
            Slice { label: "Irish"; value: 12; color: "#AB7967" }
            Slice { label: "Iceland"; value: 8; color: "#D08770" }
            Slice { label: "Ireland"; value: 10; color: "#B48EAD" }
        }
    }
}

