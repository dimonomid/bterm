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
    ../../src/gui/mainwindow/mainwindow.cpp \
    ../../src/appl/appl.cpp \
    ../../src/appl/htevent_visitor/htevent_visitor_handle.cpp \
    ../../src/util/my_util.cpp

HEADERS += ../../src/gui/mainwindow/mainwindow.h \ 
    ../../src/appl/appl.h \
    ../../src/appl/htevent_visitor/htevent_visitor_handle.h \
    ../../src/util/my_util.h
    

FORMS    += \
    ../../src/gui/mainwindow/mainwindow.ui

INCLUDEPATH += ../../src/gui/mainwindow \
               ../../src/appl/htevent_visitor \
               ../../src/appl \
               ../../src/util


