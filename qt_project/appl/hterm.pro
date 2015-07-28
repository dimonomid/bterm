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
include(../common/htcore.pri)


SOURCES += ../../src/main.cpp \
    ../../src/gui/mainwindow/mainwindow.cpp \
    ../../src/appl/appl.cpp \
    ../../src/appl/htevent_visitor/htevent_visitor_handle.cpp \
    ../../src/util/my_util.cpp \
    ../../src/gui/widgets/qplaintextedit_my.cpp \
    ../../src/appl/htiodev/htiodev_dbg.cpp \
    ../../src/gui/handler_view/handler_view.cpp \


HEADERS += ../../src/gui/mainwindow/mainwindow.h \ 
    ../../src/appl/appl.h \
    ../../src/appl/htevent_visitor/htevent_visitor_handle.h \
    ../../src/util/my_util.h \
    ../../src/gui/widgets/qplaintextedit_my.h \
    ../../src/appl/htiodev/htiodev_dbg.h \
    ../../src/gui/handler_view/handler_view.h \


FORMS    += \
    ../../src/gui/mainwindow/mainwindow.ui

INCLUDEPATH += \
    ../../src/gui/mainwindow \
    ../../src/appl/htiodev \
    ../../src/appl/htevent_visitor \
    ../../src/appl \
    ../../src/util \
    ../../src/gui/widgets \
    ../../src/gui/handler_view \


