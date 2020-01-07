#-------------------------------------------------
#
# Project created by QtCreator 2015-02-13T01:57:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QPaint
TEMPLATE = app


SOURCES += main.cpp\
    nightcharts.cpp \
    my_qlabel.cpp \
    form.cpp \
    wsbora.cpp \
    mainwindow.cpp

HEADERS  += \
    nightcharts.h \
    my_qlabel.h \
    form.h \
    wsbora.h \
    mainwindow.h

FORMS    += \
    form.ui \
    wsbora.ui \
    mainwindow.ui

RESOURCES += \
    res.qrc
