######################################################################
# Automatically generated by qmake (3.0) ?? ???? 16 16:20:33 2015
######################################################################

QT += core widgets testlib
TEMPLATE = app
TARGET = bterm-test

include(../common/appl_common.pri)
include(../common/bt_core.pri)

# Input

SOURCES += \
   ../../src/util/my_util.cpp \
   ../../src/test/test_htcodec_iso14230.cpp \
   ../../src/test/test_htdatamsg.cpp \
   ../../src/test/test_htbytearr.cpp \
   ../../src/test/test_htreqhandler.cpp \
   ../../src/test/test_main.cpp \


HEADERS += \
   ../../src/util/my_util.h \
   ../../src/test/test_htcodec_iso14230.h \
   ../../src/test/test_htdatamsg.h \
   ../../src/test/test_htbytearr.h \
   ../../src/test/test_htreqhandler.h \


INCLUDEPATH += \
   ../../src/util \

