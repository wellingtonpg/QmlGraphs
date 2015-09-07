TEMPLATE = lib
TARGET = QmlGraphs
QT += qml quick
CONFIG += qt plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = QmlGraphs

# Input
SOURCES += \
    qmlgraphs_plugin.cpp \
    src/piemodel.cpp \
    src/pie.cpp \
    src/slice.cpp

HEADERS += \
    qmlgraphs_plugin.h \
    src/piemodel.h \
    src/pie.h \    
    src/slice.h \
    src/utils.h \
    src/colorgenerator.h


DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

RESOURCES += \
    qmlgraphs.qrc

