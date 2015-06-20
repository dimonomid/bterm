
include(../common/appl_common.pri)
include(../common/ragel.pri)

RAGEL_FILES += ../../src/hterm_core/htcodec/htcodec_iso14230.cpp.rl

SOURCES += \
    ../../src/hterm_core/htdatamsg/htdatapart.cpp \
    ../../src/hterm_core/htdatamsg/htdatamsg.cpp


HEADERS += ../../src/hterm_core/htdatamsg/htdatapart.h \
    ../../src/hterm_core/htcodec/htcodec.h \
    ../../src/hterm_core/htcodec/htcodec_iso14230.h
    
INCLUDEPATH += ../../src/hterm_core/htcodec \
               ../../src/hterm_core/htdatamsg \
               ../../src/hterm_code/htdatasrc


