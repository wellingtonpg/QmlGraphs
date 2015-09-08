QmlGraphs
====================
This is a Qt Quick Extension Plugin to be used in C++/Qt projects.

### How to use
Windows:
You need to create a "QmlGraphs" folder inside your binaries folder and add "qmldir" and "QmlGraphs.dll" files.
After that you will need to import the module in each QML file you need it:

```
import QmlGraphs 1.0
```

### How to create a PieChart
Here is an example how to create a PieChart:

```
PieChart {
    anchors.fill: parent
    showShadow: true
    showSeparator: true
    showCenterColor: true
    title: "World GDP Ranking 2015"
    subtitle: "Top 6"
    legendAlignment: LegendAlignment.Bottom

    PieModel {
        Slice { label: "USA"; value: 42.87; }
        Slice { label: "China"; value: 26.52; }
        Slice { label: "Japan"; value: 9.96; }
        Slice { label: "Germany"; value: 8.07; }
        Slice { label: "UK"; value: 6.75; }
        Slice { label: "France"; value: 5.83; }
    }
}
```

Output:

![alt tag](http://imageshack.com/a/img537/170/IbQZoT.png)