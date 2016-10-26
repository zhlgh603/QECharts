#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T07:45:19
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

TARGET = EChartsDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    echartsobject.cpp \
    echartsoption.cpp

HEADERS  += mainwindow.h \
    echartsobject.h \
    echartsoption.h

FORMS    += mainwindow.ui

DISTFILES += \
    index.html \
    echarts.min.js \
    test.js \

RESOURCES += \
    echarts.qrc \
