#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T17:48:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hterm
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    gui/mainwindow/mainwindow.cpp \
    hterm_core/htdatamsg/htdatapart.cpp \
    hterm_core/htdatamsg/htdatamsg.cpp \
    hterm_core/htcodec/htcodec_iso14230.cpp

HEADERS += gui/mainwindow/mainwindow.h \
    hterm_core/htdatamsg/htdatapart.h \
    hterm_core/htcodec/htcodec_iso14230.cpp.rl

FORMS    += \
    gui/mainwindow/mainwindow.ui

INCLUDEPATH += gui/mainwindow \
               hterm_core/htdatamsg \
               hterm_core/htdatasrc \
               hterm_core/htcodec

