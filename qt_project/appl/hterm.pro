#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T17:48:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hterm
TEMPLATE = app

include(../common/appl_common.pri)
include(../common/hterm_core.pri)


SOURCES += ../../src/main.cpp \
    ../../src/gui/mainwindow/mainwindow.cpp

HEADERS += ../../src/gui/mainwindow/mainwindow.h 
    

FORMS    += \
    ../../src/gui/mainwindow/mainwindow.ui

INCLUDEPATH += ../../src/gui/mainwindow 

