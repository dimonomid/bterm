
include(../common/appl_common.pri)
include(../common/ragel.pri)

RAGEL_FILES += ../../src/hterm_core/htcodec/htcodec_iso14230.cpp.rl

SOURCES += \
    ../../src/hterm_core/htdatamsg/htdatapart.cpp \
    ../../src/hterm_core/htdatamsg/htdatamsg.cpp \
    $$PWD/../../src/hterm_core/htdatasrc/htdatasrc_dbg.cpp \
    $$PWD/../../src/hterm_core/htcore.cpp \
    $$PWD/../../src/hterm_core/htevent/htevent.cpp \
    $$PWD/../../src/hterm_core/htevent/htevent_data_raw.cpp \
    $$PWD/../../src/hterm_core/htevent/htevent_data_msg.cpp


HEADERS += ../../src/hterm_core/htdatamsg/htdatapart.h \
    ../../src/hterm_core/htcodec/htcodec.h \
    ../../src/hterm_core/htcodec/htcodec_iso14230.h \
    $$PWD/../../src/hterm_core/htdatasrc/htdatasrc_dbg.h \
    $$PWD/../../src/hterm_core/htdatasrc/htdatasrc.h \
    $$PWD/../../src/hterm_core/htcore.h \
    $$PWD/../../src/hterm_core/htevent/htevent.h \
    $$PWD/../../src/hterm_core/htevent/htevent_data_raw.h \
    $$PWD/../../src/hterm_core/htevent/htevent_data_msg.h \
    $$PWD/../../src/hterm_core/htvisitor/htvisitor.h
    
INCLUDEPATH += ../../src/hterm_core \
               ../../src/hterm_core/htcodec \
               ../../src/hterm_core/htdatamsg \
               ../../src/hterm_core/htdatasrc \
               ../../src/hterm_core/htevent \
               ../../src/hterm_core/htevent/htevent_visitor


