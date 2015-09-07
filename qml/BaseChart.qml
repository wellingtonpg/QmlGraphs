import QtQuick 2.0
import QtQuick.Layouts 1.2
import QmlGraphs 1.0

Item {
    id: baseChart
    property alias chart: chartBase.sourceComponent
    property alias legend: legendBase.sourceComponent
    property alias title: title.text
    property alias subtitle: subtitle.text
    property int legendAlignment: LegendAlignment.Bottom

    // Force the first entrance in onLegendAlignmentChanged
    Component.onCompleted: legendAlignmentChanged()

    onLegendAlignmentChanged: {
        var anc = base;
        chartBase.anchors.top = undefined
        chartBase.anchors.left = undefined
        chartBase.anchors.bottom = undefined
        chartBase.anchors.right = undefined

        legendBase.anchors.top = undefined
        legendBase.anchors.left = undefined
        legendBase.anchors.bottom = undefined
        legendBase.anchors.right = undefined

        if (legendAlignment === LegendAlignment.Left) {
            legendBase.anchors.left = anc.left
            chartBase.anchors.left = legendBase.right
            chartBase.anchors.leftMargin = 10
        }
        else if (legendAlignment === LegendAlignment.Bottom) {
            chartBase.anchors.top = anc.top
            legendBase.anchors.top = chartBase.bottom
            legendBase.anchors.topMargin = 10
        }
        else if (legendAlignment === LegendAlignment.Right) {
            chartBase.anchors.left = anc.left
            legendBase.anchors.left = chartBase.right
            legendBase.anchors.leftMargin = 10
        }
        else if (legendAlignment === LegendAlignment.Top) {
            legendBase.anchors.top = anc.top
            chartBase.anchors.top = legendBase.bottom
            chartBase.anchors.topMargin = 10
        }
    }

    Text {
        id: title
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: Style.TITLE_BOLD
        font.pixelSize: Style.TITLE_PIXELSIZE
    }

    Text {
        id: subtitle
        anchors {
            horizontalCenter: title.horizontalCenter
            top: title.bottom
        }
    }

    Item {
        id: base
        anchors {
            top: subtitle.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            margins: 10
        }
        Loader {
            id: chartBase
            width: legendAlignment === LegendAlignment.Left ||
                   legendAlignment === LegendAlignment.Right ?
                   base.width * 0.8 : base.width

            height: legendAlignment === LegendAlignment.Bottom ||
                    legendAlignment === LegendAlignment.Top ?
                    base.height * 0.9 : base.height
        }
        Loader {
            id: legendBase
            width: legendAlignment === LegendAlignment.Left ||
                   legendAlignment === LegendAlignment.Right ?
                   base.width * 0.2 : base.width

            height: legendAlignment === LegendAlignment.Bottom ||
                    legendAlignment === LegendAlignment.Top ?
                    base.height * 0.1 : base.height
        }
    }
}

