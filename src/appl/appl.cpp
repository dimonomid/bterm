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

#include "bt_codec.h"
#include "bt_codec_iso14230.h"

#include "bt_iodev.h"
#include "bt_iodev_dbg.h"

#include "bt_datamsg.h"
#include "bt_project_storage_xml.h"




//TODO: remove
#include <QtQml>
#include <QJSEngine>
#include <QJSValue>
#include <QVariant>
#include <QDebug>
#include "bytearr_read.h"
#include "bytearr_read_write.h"
#include "my_util.h"

using namespace BTCore;
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
    p_sett(std::make_shared<XmlSettings>("bterm_sett.xml")),
    p_io_dev(nullptr),
    p_project(nullptr),

    proj_filename(""),

    bt_event_visitor__appl_handle(*this),
    p_main_window(std::unique_ptr<MainWindow>(new MainWindow(*this)))
{
    initSettings();

    //-- create debug IO device
    //   TODO: change to real
    {
        p_io_dev = std::make_shared<IODevDbg>();

        connect(
                this->p_io_dev.get(), &IODev::openStatusChanged,
                this, &Appl::onIODevOpenStatusChanged
               );
        connect(
                this->p_io_dev.get(), &IODev::error,
                this, &Appl::onIODevError
               );
    }

    //-- create event accumulators

    p_events_data_raw = std::unique_ptr<EventsAcc<EventDataRaw>>{
        new EventsAcc<EventDataRaw>(1000/*TODO: settings*/)
    };

    p_events_data_msg = std::unique_ptr<EventsAcc<EventDataMsg>>{
        new EventsAcc<EventDataMsg>(1000/*TODO: settings*/)
    };

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
    emit event(p_event);
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

/**
 *
 */
void Appl::connectToCurProject()
{
    connect(
            p_project.get(), &Project::event,
            this, &Appl::onEvent
           );

    //-- just forward reqHandlerTitleChanged() signal
    connect(
            p_project.get(), &Project::reqHandlerTitleChanged,
            this, &Appl::reqHandlerTitleChanged
           );

    //-- set IODev to newly created project, so that it can talk
    p_project->setIODev(p_io_dev);

    emit projectOpened(proj_filename, p_project);
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

void Appl::newProject()
{
    //-- close currently opened project (if any)
    closeProject();

    p_project = std::make_shared<Project>();

    p_project->setUnsaved(true);

    cryEventSys(
            EventSys::Level::INFO,
            tr("New project has been created")
            );

    rememberProjectFilename("");

    connectToCurProject();
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

        p_project->setUnsaved(false);

        cryEventSys(
                EventSys::Level::INFO,
                tr("Project \"") + filename + tr("\" opened successfully")
                );

        rememberProjectFilename(fileinfo.absoluteFilePath());

        connectToCurProject();

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

            p_project->setUnsaved(false);

            cryEventSys(
                    EventSys::Level::INFO,
                    tr("Project \"") + filename + tr("\" saved successfully")
                    );

            rememberProjectFilename(fileinfo.absoluteFilePath());

            emit projectSaved(proj_filename, p_project);

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

void Appl::onEvent(std::shared_ptr<Event> p_event)
{
    //-- handle event with visitor
    p_event->accept(bt_event_visitor__appl_handle);

    //-- forward the event
    emit event(p_event);
}

/**
 * Called when IO device is opened or closed
 */
void Appl::onIODevOpenStatusChanged(bool opened)
{
    QString msg;
    if (opened){
        msg = "IO Device \"" + p_io_dev->toString() + "\" opened";
    } else {
        msg = "IO Device \"" + p_io_dev->toString() + "\" closed";
    }

    auto p_event = std::make_shared<EventSys>(EventSys::Level::INFO, msg);
    emit event(p_event);

    emit ioDevOpenStatusChanged(opened);
}

/**
 * Called whenever IO error occurs
 */
void Appl::onIODevError(QString error_msg)
{
    auto p_event = std::make_shared<EventSys>(
            EventSys::Level::ERROR,
            "IO error: " + error_msg
            );
    emit event(p_event);
}


/* protected    */

/* public       */


