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

include(../common/ragel.pri)

RAGEL_FILES += ../../src/hterm_core/htcodec/htcodec_iso14230.cpp.rl

SOURCES += ../../src/main.cpp \
    ../../src/gui/mainwindow/mainwindow.cpp \
    ../../src/hterm_core/htdatamsg/htdatapart.cpp \
    ../../src/hterm_core/htdatamsg/htdatamsg.cpp

HEADERS += ../../src/gui/mainwindow/mainwindow.h \
    ../../src/hterm_core/htdatamsg/htdatapart.h \
    ../../src/hterm_core/htcodec/htcodec.h \
    ../../src/hterm_core/htcodec/htcodec_iso14230.h
    

FORMS    += \
    ../../src/gui/mainwindow/mainwindow.ui

INCLUDEPATH += ../../src/gui/mainwindow \
               ../../src/hterm_core/htdatamsg \
               ../../src/hterm_core/htdatasrc \
               ../../src/hterm_core/htcodec

