/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <memory>



#include "appl.h"
#include "xmlsettings.h"

#include "htcodec.h"
#include "htcodec_iso14230.h"

#include "htiodev.h"
#include "htiodev_dbg.h"

#include "htdatamsg.h"

//#include "htevent_data_raw.h"
//#include "htevent_data_msg.h"



//TODO: remove
#include <QtQml>
#include <QJSEngine>
#include <QJSValue>
#include <QVariant>
#include <QDebug>
#include "bytearr_read.h"
#include "bytearr_read_write.h"
#include "my_util.h"

using namespace HTCore;
using namespace std;

/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const QString Appl::SETT_KEY__APPL = "appl";
const QString Appl::SETT_KEY__APPL__LAST_PROJECT_FILENAME =
SETT_KEY__APPL + "/last_project_filename";



/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Appl::Appl() :
    p_sett(std::make_shared<XmlSettings>("hterm_sett.xml")),
    p_codec(nullptr),
    p_io_dev(nullptr),
    p_project(nullptr),

    proj_filename(""),

    htevent_visitor_handle(*this),
    p_main_window(std::unique_ptr<MainWindow>(new MainWindow(*this)))
{
    initSettings();

    p_io_dev = std::make_shared<IODevDbg>();
    p_codec = std::make_shared<Codec_ISO14230>(0x01, 0x02);

    p_events_data_raw = std::unique_ptr<EventsAcc<EventDataRaw>>{
        new EventsAcc<EventDataRaw>(1000/*TODO: settings*/)
    };

    p_events_data_msg = std::unique_ptr<EventsAcc<EventDataMsg>>{
        new EventsAcc<EventDataMsg>(1000/*TODO: settings*/)
    };


#if 0
    {
        qmlRegisterType<ByteArrReadWrite>("test", 1, 0, "ByteArrReadWrite");


        QJSEngine engine;

        ByteArrFactory ba_factory {};
        QJSValue ba_factory_jsval = engine.newQObject(&ba_factory);

        QJSValue func = engine.evaluate(
                R"(

            (function(baFactory) {

             var ba = baFactory.createByteArrReadWrite();
             ba.putU08(2, 0x08);

             return ba;

             });

        )"
                );

        qDebug() << "func: " << func.toString();

        QJSValue ba_jsval = func.call(
                QJSValueList() << ba_factory_jsval
                );

        qDebug() << "isQObject: " << ba_jsval.isQObject();
        qDebug() << "toString: " << ba_jsval.toString();
    }
#endif

#if 0
    {
        QJSEngine engine;

        QJSValue myCodec = engine.evaluate(
                R"(

            (function() {

             var rawData;

             reset();

             return {
feedRawData: feedRawData,
getTest: function() {
return rawData.length;
}
};


function feedRawData(num) {
rawData.push(num);
};

function reset() {
rawData = [];
};

})();

)"
);



myCodec.property("feedRawData").call(
        QJSValueList() << (double)1
        );
qDebug() << "test: " << myCodec.property("getTest").call().toString();
myCodec.property("feedRawData").call(
        QJSValueList() << (double)1
        );
qDebug() << "test: " << myCodec.property("getTest").call().toString();
}
#endif


#if 0
{
    QJSEngine engine;

    QJSValue val = engine.evaluate(
            "({a: 1, b: 2});"
            );

    qDebug() << "val: " << val.toVariant();
}
#endif

#if 0
{
    QJSEngine engine;
    QJSValue val = engine.evaluate(
            "test();"
            );

    if (val.isError()){
        qDebug() << "error, variant: " << val.toVariant();

        qDebug() << "message: " << val.property("message").toString();
        qDebug() << "lineNumber: " << val.property("lineNumber").toString();
    }
    qDebug() << "val: " << val.toVariant();
}
#endif

#if 0
{
    QJSEngine engine;

    QJSValue val = engine.evaluate(
            "print('123');"
            );

    if (val.isError()){
        qDebug() << "error: " << val.toString();
    }

    qDebug() << "val: " << val.toVariant();
}
#endif


#if 0
{
    QJSEngine engine;
    QJSValue result;

    std::vector<uint8_t> in_data{0x61, 0x01};

    ByteArrRead ba_in {in_data};
    ByteArrReadWrite ba_out {};

    QJSValue ba_in_scrval = engine.newQObject(&ba_in);
    QJSValue ba_out_scrval = engine.newQObject(&ba_out);
    QJSValue script_ctx = engine.evaluate("({})");

    QJSValue func = engine.evaluate(
            "(function(inputArr, outputArr){ "
            "     this.c = 123;"

            "     if (inputArr.getU08(0) === 0x61){"
            "        outputArr.setFillByte(0xaa);"
            "        outputArr.putU08(4, 0x10);"
            "        outputArr.putU08(1, 0xff);"
            "     };"
            "     return {"
            "        handled: true"
            "     };"
            " })"
            );

    if (engine.hasUncaughtException()){
        qDebug() << "exception: " << func.toVariant();
    } else {
        QJSValue returned = func.call(
                script_ctx,
                QJSValueList() << ba_in_scrval << ba_out_scrval << script_ctx
                );

        qDebug() << "in: "  << MyUtil::byteArrayToHex(*ba_in.getData());
        qDebug() << "out: " << MyUtil::byteArrayToHex(*ba_out.getData());
        qDebug() << "script_ctx: " << script_ctx.toVariant().toMap();

        if (engine.hasUncaughtException()){
            qDebug() << "exception: " << returned.toVariant();
        } else {
            qDebug() << "returned: " << returned.toVariant();
            qDebug() << "returned handled: " << returned.toVariant().toMap()["handled"].toBool();
        }
    }

}
#endif


    openProject("dummy");

    this->p_main_window->showInRestoredState();

}

Appl::~Appl()
{
}


/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

void Appl::initSettings()
{
    this->p_sett->value(SETT_KEY__APPL__LAST_PROJECT_FILENAME,  "");
}



/* protected    */

/* public       */

void Appl::openProject(QString filename)
{
    auto file = std::make_shared<QFile>(filename);
    QFileInfo fileinfo {*file};

    // TODO: really open project
    proj_filename = fileinfo.absoluteFilePath();
    this->p_sett->setValue(
            SETT_KEY__APPL__LAST_PROJECT_FILENAME, proj_filename
            );

    p_project = std::make_shared<Project>(p_codec, p_io_dev);

    connect(
            p_project.get(), &Project::eventDataRaw,
            this, &Appl::onNewDataRaw
           );

    connect(
            p_project.get(), &Project::eventDataMsg,
            this, &Appl::onNewDataMsg
           );

    //-- just forward reqHandlerNameChanged() signal
    connect(
            p_project.get(), &Project::reqHandlerNameChanged,
            this, &Appl::reqHandlerNameChanged
           );



    emit projectOpened(p_project);
}

QString Appl::getProjectFilename() const
{
    return proj_filename;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

#if 0
void Appl::onEvent(const std::shared_ptr<Event> &p_event)
{
    p_event->accept(htevent_visitor_handle);
}
#endif

void Appl::onNewDataRaw(std::shared_ptr<EventDataRaw> p_event)
{
    p_events_data_raw->addEvent(p_event);

    emit eventDataRaw(p_event);
}

void Appl::onNewDataMsg(std::shared_ptr<EventDataMsg> p_event)
{
    p_events_data_msg->addEvent(p_event);

    emit eventDataMsg(p_event);
}

#if 0
void Appl::onHandlerNameChanged(
        const ReqHandler *p_handler,
        const QString &name
        )
{
    emit eventDataMsg(p_event);
}
#endif





#if 0
void Appl::onNewDataRaw(const std::vector<uint8_t> &data)
{
    //TODO
}

void Appl::onNewDataMsg(const DataMsg &msg)
{
    //TODO
}
#endif

/* protected    */

/* public       */


