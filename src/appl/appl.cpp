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
#include "htproject_storage_xml.h"




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
    p_io_dev(nullptr),
    p_project(nullptr),

    proj_filename(""),

    htevent_visitor_handle(*this),
    p_main_window(std::unique_ptr<MainWindow>(new MainWindow(*this)))
{
    initSettings();

    //-- create debug IO device
    //   TODO: change to real
    p_io_dev = std::make_shared<IODevDbg>();

    //-- create event accumulators

    p_events_data_raw = std::unique_ptr<EventsAcc<EventDataRaw>>{
        new EventsAcc<EventDataRaw>(1000/*TODO: settings*/)
    };

    p_events_data_msg = std::unique_ptr<EventsAcc<EventDataMsg>>{
        new EventsAcc<EventDataMsg>(1000/*TODO: settings*/)
    };


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



    //-- if we have some previously-opened project, and it still exists,
    //   then open it
    {
        QString last_project_filename = getLastProjectFilename();
        if (
                !last_project_filename.isEmpty() 
                && QFile::exists(last_project_filename)
           )
        {
            openProject(last_project_filename);
        }
    }

#if 0
    openProject("/home/dimon/projects/hterm/hterm/stuff/test_proj/test_proj.xml");
    saveProject("/home/dimon/projects/hterm/hterm/stuff/test_proj/test_proj.xml");
#endif

    //-- show main window (restoring the previously saved state, if any)
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


/**
 * Initialize appl settings with default values for unspecified ones
 */
void Appl::initSettings()
{
    this->p_sett->value(SETT_KEY__APPL__LAST_PROJECT_FILENAME,  "");
}

/**
 * Emit (cry) system event
 */
void Appl::cryEventSys(EventSys::Level level, QString text)
{
    auto p_event = std::make_shared<EventSys>(level, text);
    emit eventSys(p_event);
}

/**
 * Remember project filename: called after project is loaded or saved
 */
void Appl::rememberProjectFilename(QString filename)
{
    proj_filename = filename;
    this->p_sett->setValue(
            SETT_KEY__APPL__LAST_PROJECT_FILENAME, proj_filename
            );
}


/* protected    */

/* public       */

void Appl::closeProject()
{
    //-- if we have some currently opened project, cry that it is
    //   going to be closed
    if (p_project != nullptr){

        //-- Note: we don't disconnect() from devices' signals manually, since
        //   QObject does that for us, and if we do that, then we're unable to
        //   send signals from destructor of the sender (well, we are able, but
        //   nobody will care)

        cryEventSys(
                EventSys::Level::INFO,
                tr("Project \"") + proj_filename + tr("\" closed")
                );


        emit projectBeforeClose(p_project);
    }

    p_project = nullptr;
    proj_filename = tr("");
}

void Appl::openProject(QString filename)
{
    //-- close currently opened project (if any)
    closeProject();

    auto file = std::make_shared<QFile>(filename);
    QFileInfo fileinfo {*file};

    file->open(QIODevice::ReadOnly);

    //-- try to read project from xml file
    ProjectStorageXML storage_xml (file);

    //-- subscribe to the reader's events
    //   (there may be some warnings or errors)
    //   TODO
    //connect(&storage_xml, &ProjectReaderXML::event, this, &Appl::onDMEvent);

    try {
        p_project = storage_xml.readProject();
        //-- project is read successfully
        //   let's save filename and notify the listeners

        cryEventSys(
                EventSys::Level::INFO,
                tr("Project \"") + filename + tr("\" opened successfully")
                );

        rememberProjectFilename(fileinfo.absoluteFilePath());

        //-- set IODev to newly created project, so that it can talk
        p_project->setIODev(p_io_dev);

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

    } catch (std::invalid_argument e){
        //-- there was some error during project read

        cryEventSys(
                EventSys::Level::ERROR,
                tr("Error during opening the project \"") 
                + filename
                + tr("\": ")
                + e.what()
                );
    }

    file->close();
}

void Appl::saveProject(QString filename)
{
    //-- if given filename is empty, use current project filename
    if (filename.isEmpty()){
        filename = getProjectFilename();
    }

    //-- if filename is, after all, specified, then proceed
    //   with saving
    if (!filename.isEmpty()){
        auto file = std::make_shared<QFile>(filename);
        QFileInfo fileinfo {*file};

        file->open(QIODevice::WriteOnly);

        //-- try to read project from xml file
        ProjectStorageXML storage_xml (file);

        try {
            storage_xml.saveProject(p_project);
            //-- project is read successfully
            //   let's save filename and notify the listeners

            cryEventSys(
                    EventSys::Level::INFO,
                    tr("Project \"") + filename + tr("\" saved successfully")
                    );

        } catch (std::invalid_argument e){
            //-- there was some error during project read

            cryEventSys(
                    EventSys::Level::ERROR,
                    tr("Error during saving the project \"") 
                    + filename
                    + tr("\": ")
                    + e.what()
                    );
        }

        file->close();

        rememberProjectFilename(fileinfo.absoluteFilePath());
    } else {
        cryEventSys(
                EventSys::Level::ERROR,
                tr("Can't save current project, since there's no filename")
                );
    }
}

QString Appl::getProjectFilename() const
{
    return proj_filename;
}

QString Appl::getLastProjectFilename() const
{
    return this->p_sett->value(SETT_KEY__APPL__LAST_PROJECT_FILENAME).toString();
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

/**
 * Called when new `EventDataRaw` happened
 */
void Appl::onNewDataRaw(std::shared_ptr<EventDataRaw> p_event)
{
    p_events_data_raw->addEvent(p_event);

    emit eventDataRaw(p_event);
}

/**
 * Called when new `EventDataMsg` happened
 */
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


