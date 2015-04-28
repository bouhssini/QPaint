#-------------------------------------------------
#
# Project created by QtCreator 2015-02-13T01:57:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QPaint
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    nightcharts.cpp \
    my_qlabel.cpp

HEADERS  += dialog.h \
    nightcharts.h \
    my_qlabel.h

FORMS    += dialog.ui

RESOURCES += \
    res.qrc
