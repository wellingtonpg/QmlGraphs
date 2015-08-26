TEMPLATE = app

QT += qml quick
CONFIG += c++11

HEADERS += \
    src/pie.h \
    src/basegraph.h \
    src/piemodel.h \
    src/slice.h

SOURCES += main.cpp \
    src/pie.cpp \
    src/basegraph.cpp \
    src/piemodel.cpp \
    src/slice.cpp

RESOURCES += qml.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

