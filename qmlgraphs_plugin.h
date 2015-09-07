#ifndef QMLGRAPHS_PLUGIN_H
#define QMLGRAPHS_PLUGIN_H

#include <QQmlExtensionPlugin>

class QmlGraphsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // QMLGRAPHS_PLUGIN_H

