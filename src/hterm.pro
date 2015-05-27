#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T17:48:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hterm
TEMPLATE = app


SOURCES += main.cpp \
    gui/mainwindow/mainwindow.cpp

HEADERS += gui/mainwindow/mainwindow.h

FORMS    += \
    gui/mainwindow/mainwindow.ui

INCLUDEPATH += gui/mainwindow

