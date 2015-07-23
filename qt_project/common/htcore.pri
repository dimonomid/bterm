
include(../common/appl_common.pri)
include(../common/ragel.pri)

QT += script

RAGEL_FILES += ../../src/htcore/htcodec/htcodec_iso14230.cpp.rl

SOURCES += \
    ../../src/htcore/htdatamsg/htdatapart.cpp \
    ../../src/htcore/htdatamsg/htdatamsg.cpp \
    $$PWD/../../src/htcore/htproject/htproject.cpp \
    $$PWD/../../src/htcore/htevent/htevent.cpp \
    $$PWD/../../src/htcore/htevent/htevent_data_raw.cpp \
    $$PWD/../../src/htcore/htevent/htevent_data_msg.cpp \
    $$PWD/../../src/htcore/scripts/bytearr.cpp \


HEADERS += ../../src/htcore/htdatamsg/htdatapart.h \
    ../../src/htcore/htcodec/htcodec.h \
    ../../src/htcore/htcodec/htcodec_iso14230.h \
    $$PWD/../../src/htcore/htiodev/htiodev.h \
    $$PWD/../../src/htcore/htproject/htproject.h \
    $$PWD/../../src/htcore/htevent/htevent.h \
    $$PWD/../../src/htcore/htevent/htevent_data_raw.h \
    $$PWD/../../src/htcore/htevent/htevent_data_msg.h \
    $$PWD/../../src/htcore/htevent/htevent_visitor/htevent_visitor.h \
    $$PWD/../../src/htcore/htevents_acc.h \
    $$PWD/../../src/htcore/scripts/bytearr.h \


INCLUDEPATH += ../../src/htcore \
               ../../src/htcore/htproject \
               ../../src/htcore/htcodec \
               ../../src/htcore/htdatamsg \
               ../../src/htcore/htiodev \
               ../../src/htcore/htevent \
               ../../src/htcore/htevent/htevent_visitor \
               ../../src/htcore/scripts \


