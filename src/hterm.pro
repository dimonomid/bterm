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

ragel.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}    # output file (input filename without .rl)
ragel.input = RAGEL_FILES         # list of input files
ragel.commands = ragel ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}    #command
ragel.variable_out = SOURCES    # where output files should be placed
ragel.name = RAGEL    # name (for internal qmake usage)

QMAKE_EXTRA_COMPILERS += ragel

RAGEL_FILES += hterm_core/htcodec/htcodec_iso14230.cpp.rl

SOURCES += main.cpp \
    gui/mainwindow/mainwindow.cpp \
    hterm_core/htdatamsg/htdatapart.cpp \
    hterm_core/htdatamsg/htdatamsg.cpp

HEADERS += gui/mainwindow/mainwindow.h \
    hterm_core/htdatamsg/htdatapart.h \
    hterm_core/htcodec/htcodec.h \
    hterm_core/htcodec/htcodec_iso14230.h
    

FORMS    += \
    gui/mainwindow/mainwindow.ui

INCLUDEPATH += gui/mainwindow \
               hterm_core/htdatamsg \
               hterm_core/htdatasrc \
               hterm_core/htcodec

