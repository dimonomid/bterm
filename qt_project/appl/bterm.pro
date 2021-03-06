#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T17:48:49
#
#-------------------------------------------------

QT       += core gui xml serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bterm
TEMPLATE = app

include(../common/appl_common.pri)
include(../common/bt_core.pri)


SOURCES += \
    ../../src/main.cpp \
    ../../src/gui/mainwindow/mainwindow.cpp \
    ../../src/gui/bt_project_view/bt_project_view.cpp \
    ../../src/gui/bt_codec_view/bt_codec_iso14230_view.cpp \
    ../../src/gui/bt_codec_view/bt_codec_empty_view.cpp \
    ../../src/gui/bt_codec_view/bt_codec_visitor/bt_codec_visitor__view_create.cpp \
    ../../src/gui/bt_iodev_view/bt_iodev_view.cpp \
    ../../src/gui/mainwindow/bt_event_visitor/bt_event_visitor__gui_handle.cpp \
    ../../src/appl/appl.cpp \
    ../../src/appl/bt_event_visitor/bt_event_visitor__appl_handle.cpp \
    ../../src/util/my_util.cpp \
    ../../src/gui/widgets/qplaintextedit_my.cpp \
    ../../src/appl/bt_iodev/bt_iodev_dbg.cpp \
    ../../src/appl/bt_iodev/bt_iodev_serial.cpp \
    ../../src/gui/bt_req_handler_view/bt_req_handler_view.cpp \
    ../../src/util/xmlsettings/xmlsettings.cpp \
    ../../src/gui/appl_sett_dialog/appl_sett_dialog.cpp \


HEADERS += \
    ../../src/gui/mainwindow/mainwindow.h \
    ../../src/gui/bt_project_view/bt_project_view.h \
    ../../src/gui/bt_codec_view/bt_codec_view.h \
    ../../src/gui/bt_codec_view/bt_codec_iso14230_view.h \
    ../../src/gui/bt_codec_view/bt_codec_empty_view.h \
    ../../src/gui/bt_codec_view/bt_codec_visitor/bt_codec_visitor__view_create.h \
    ../../src/gui/bt_iodev_view/bt_iodev_view.h \
    ../../src/gui/mainwindow/bt_event_visitor/bt_event_visitor__gui_handle.h \
    ../../src/appl/appl.h \
    ../../src/appl/bt_event_visitor/bt_event_visitor__appl_handle.h \
    ../../src/util/my_util.h \
    ../../src/gui/widgets/qplaintextedit_my.h \
    ../../src/appl/bt_iodev/bt_iodev_dbg.h \
    ../../src/appl/bt_iodev/bt_iodev_serial.h \
    ../../src/gui/bt_req_handler_view/bt_req_handler_view.h \
    ../../src/util/xmlsettings/xmlsettings.h \
    ../../src/gui/appl_sett_dialog/appl_sett_dialog.h \


FORMS    += \
    ../../src/gui/mainwindow/mainwindow.ui \
    ../../src/gui/bt_project_view/bt_project_view.ui \
    ../../src/gui/bt_codec_view/bt_codec_iso14230_view.ui \
    ../../src/gui/bt_iodev_view/bt_iodev_view.ui \
    ../../src/gui/appl_sett_dialog/appl_sett_dialog.ui

INCLUDEPATH += \
    ../../src/gui/mainwindow \
    ../../src/gui/mainwindow/bt_event_visitor \
    ../../src/gui/bt_project_view \
    ../../src/gui/bt_codec_view \
    ../../src/gui/bt_codec_view/bt_codec_visitor \
    ../../src/gui/bt_iodev_view \
    ../../src/appl/bt_iodev \
    ../../src/appl/bt_event_visitor \
    ../../src/appl \
    ../../src/util \
    ../../src/gui/widgets \
    ../../src/gui/bt_req_handler_view \
    ../../src/util/xmlsettings \
    ../../src/gui/appl_sett_dialog \

DISTFILES +=

RESOURCES += \
    ../../resources/res.qrc


