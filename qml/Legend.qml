import QtQuick 2.0
import QmlGraphs 1.0

Item {
    id: legend
    property PieModel model

    Rectangle {
        border.width: 0
        border.color: "#999999"
        clip: true

        anchors.centerIn: parent
        anchors.margins: 10
        width: parent.width
        height: flow.height + 10

        Flow {
            id: flow
            spacing: 15
            anchors.left: parent.left
            anchors.right: parent.right

            Repeater {
                id: repeater
                anchors.horizontalCenter: parent.horizontalCenter
                model: legend.model.slices
                Row {
                    spacing: 5
                    Rectangle {
                        width: 12
                        height: width
                        radius: width * 0.5
                        color: modelData.color
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        text: modelData.label
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }
}
