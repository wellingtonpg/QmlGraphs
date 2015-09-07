import QtQuick 2.0
import QmlGraphs 1.0

BaseChart {
    id: base
    default property PieModel model
    property bool showShadow
    property bool showSeparator
    property bool showCenterColor: parent.color

    antialiasing: true

    chart: Pie {
        antialiasing: base.antialiasing
        model: base.model
        showShadow: base.showShadow
        showSeparator: base.showSeparator
        showCenterColor: base.showCenterColor

        PopUp {
            visible: selectedSlice != null
            text: visible ? selectedSlice.label + " (" + selectedSlice.value + "%)" : ""
            x: visible ? selectedSlice.centerPoint.x - (width / 2) : 0
            y: visible ? selectedSlice.centerPoint.y - (height / 2) : 0
        }
    }

    legend: Legend {
        model: base.model
    }
}

