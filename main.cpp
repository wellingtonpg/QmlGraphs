#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "src/pie.h"
#include "src/piemodel.h"
#include "src/slice.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Pie>("QmlGraphs", 1, 0, "Pie");
    qmlRegisterType<PieModel>("QmlGraphs", 1, 0, "PieModel");
    qmlRegisterType<Slice>("QmlGraphs", 1, 0, "Slice");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

