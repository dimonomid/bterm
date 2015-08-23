
include(../common/appl_common.pri)
include(../common/ragel.pri)

QT += qml xml

RAGEL_FILES += ../../src/bt_core/bt_codec/bt_codec_iso14230.cpp.rl

SOURCES += \
    ../../src/bt_core/bt_codec/bt_codec.cpp \
    ../../src/bt_core/bt_codec/bt_codec_factory/bt_codec_factory.cpp \
    ../../src/bt_core/bt_codec/bt_codec_transparent.cpp \
    ../../src/bt_core/bt_datamsg/bt_datapart.cpp \
    ../../src/bt_core/bt_datamsg/bt_datamsg.cpp \
    ../../src/bt_core/bt_project/bt_project.cpp \
    ../../src/bt_core/bt_project_storage_xml/bt_project_storage_xml.cpp \
    ../../src/bt_core/bt_project_storage_xml/bt_codec_visitor/bt_codec_visitor__save_xml.cpp \
    ../../src/bt_core/bt_project_storage_xml/bt_codec_visitor/bt_codec_visitor__load_from_xml.cpp \
    ../../src/bt_core/bt_event/bt_event.cpp \
    ../../src/bt_core/bt_event/bt_event_data_raw.cpp \
    ../../src/bt_core/bt_event/bt_event_data_msg.cpp \
    ../../src/bt_core/bt_event/bt_event_sys.cpp \
    ../../src/bt_core/bt_reqhandler/bt_reqhandler.cpp \
    ../../src/bt_core/scripts/bytearr_read.cpp \
    ../../src/bt_core/scripts/bytearr_read_write.cpp \
    ../../src/bt_core/scripts/script_factory.cpp \


HEADERS += ../../src/bt_core/bt_datamsg/bt_datapart.h \
    ../../src/bt_core/bt_codec/bt_codec.h \
    ../../src/bt_core/bt_codec/bt_codec_iso14230.h \
    ../../src/bt_core/bt_codec/bt_codec_transparent.h \
    ../../src/bt_core/bt_codec/bt_codec_factory/bt_codec_factory.h \
    ../../src/bt_core/bt_iodev/bt_iodev.h \
    ../../src/bt_core/bt_project/bt_project.h \
    ../../src/bt_core/bt_project_storage_xml/bt_project_storage_xml.h \
    ../../src/bt_core/bt_project_storage_xml/bt_codec_visitor/bt_codec_visitor__save_xml.h \
    ../../src/bt_core/bt_project_storage_xml/bt_codec_visitor/bt_codec_visitor__load_from_xml.h \
    ../../src/bt_core/bt_event/bt_event.h \
    ../../src/bt_core/bt_event/bt_event_data_raw.h \
    ../../src/bt_core/bt_event/bt_event_data_msg.h \
    ../../src/bt_core/bt_event/bt_event_sys.h \
    ../../src/bt_core/bt_event/bt_event_visitor/bt_event_visitor.h \
    ../../src/bt_core/bt_events_acc.h \
    ../../src/bt_core/bt_reqhandler/bt_reqhandler.h \
    ../../src/bt_core/scripts/bytearr_read.h \
    ../../src/bt_core/scripts/bytearr_read_write.h \
    ../../src/bt_core/scripts/script_factory.h \


INCLUDEPATH += ../../src/bt_core \
               ../../src/bt_core/bt_project \
               ../../src/bt_core/bt_project_storage_xml \
               ../../src/bt_core/bt_project_storage_xml/bt_codec_visitor \
               ../../src/bt_core/bt_codec \
               ../../src/bt_core/bt_codec/bt_codec_visitor \
               ../../src/bt_core/bt_codec/bt_codec_factory \
               ../../src/bt_core/bt_datamsg \
               ../../src/bt_core/bt_iodev \
               ../../src/bt_core/bt_event \
               ../../src/bt_core/bt_event/bt_event_visitor \
               ../../src/bt_core/bt_reqhandler \
               ../../src/bt_core/scripts \


