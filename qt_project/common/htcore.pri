
include(../common/appl_common.pri)
include(../common/ragel.pri)

QT += qml

RAGEL_FILES += ../../src/htcore/htcodec/htcodec_iso14230.cpp.rl

SOURCES += \
    ../../src/htcore/htdatamsg/htdatapart.cpp \
    ../../src/htcore/htdatamsg/htdatamsg.cpp \
    ../../src/htcore/htproject/htproject.cpp \
    ../../src/htcore/htproject_storage_xml/htproject_storage_xml.cpp \
    ../../src/htcore/htproject_storage_xml/htcodec_visitor/htcodec_visitor__save_xml.cpp \
    ../../src/htcore/htevent/htevent.cpp \
    ../../src/htcore/htevent/htevent_data_raw.cpp \
    ../../src/htcore/htevent/htevent_data_msg.cpp \
    ../../src/htcore/htevent/htevent_sys.cpp \
    ../../src/htcore/htreqhandler/htreqhandler.cpp \
    ../../src/htcore/scripts/bytearr_read.cpp \
    ../../src/htcore/scripts/bytearr_read_write.cpp \
    ../../src/htcore/scripts/script_factory.cpp \


HEADERS += ../../src/htcore/htdatamsg/htdatapart.h \
    ../../src/htcore/htcodec/htcodec.h \
    ../../src/htcore/htcodec/htcodec_iso14230.h \
    ../../src/htcore/htiodev/htiodev.h \
    ../../src/htcore/htproject/htproject.h \
    ../../src/htcore/htproject_storage_xml/htproject_storage_xml.h \
    ../../src/htcore/htproject_storage_xml/htcodec_visitor/htcodec_visitor__save_xml.h \
    ../../src/htcore/htevent/htevent.h \
    ../../src/htcore/htevent/htevent_data_raw.h \
    ../../src/htcore/htevent/htevent_data_msg.h \
    ../../src/htcore/htevent/htevent_sys.h \
    ../../src/htcore/htevent/htevent_visitor/htevent_visitor.h \
    ../../src/htcore/htevents_acc.h \
    ../../src/htcore/htreqhandler/htreqhandler.h \
    ../../src/htcore/scripts/bytearr_read.h \
    ../../src/htcore/scripts/bytearr_read_write.h \
    ../../src/htcore/scripts/script_factory.h \


INCLUDEPATH += ../../src/htcore \
               ../../src/htcore/htproject \
               ../../src/htcore/htproject_storage_xml \
               ../../src/htcore/htproject_storage_xml/htcodec_visitor \
               ../../src/htcore/htcodec \
               ../../src/htcore/htcodec/htcodec_visitor \
               ../../src/htcore/htdatamsg \
               ../../src/htcore/htiodev \
               ../../src/htcore/htevent \
               ../../src/htcore/htevent/htevent_visitor \
               ../../src/htcore/htreqhandler \
               ../../src/htcore/scripts \


