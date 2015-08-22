/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _APPL_H
#define _APPL_H


/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <memory>

#include <QObject>

#include "mainwindow.h"

#include "htproject.h"
#include "htevents_acc.h"
#include "htiodev.h"
#include "htcodec.h"
#include "htevent_sys.h"

#include "htevent_visitor_handle.h"




class XmlSettings;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

/**
 * Class that essentially provides a "glue" for two other application parties:
 * `#HTCore` and GUI.
 *
 * It provides project open/close functionality, and also settings that persist
 * across multiple application invocations. See method descriptions for
 * details.
 *
 * For an overview of application implementation, see \ref impl_overview
 */
class Appl : public QObject
{
Q_OBJECT;
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
    public:
    explicit Appl();
    ~Appl();


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- instance of application settings (used by all modules of the application),
    //   returned by settings() method
    std::shared_ptr<XmlSettings> p_sett;

    //-- IO device (serial port implementation)
    std::shared_ptr<HTCore::IODev> p_io_dev;

    //-- current project
    std::shared_ptr<HTCore::Project> p_project;

    //-- accumulator of data raw events
    std::unique_ptr<HTCore::EventsAcc<HTCore::EventDataRaw>> p_events_data_raw;

    //-- accumulator of data message events
    std::unique_ptr<HTCore::EventsAcc<HTCore::EventDataMsg>> p_events_data_msg;

    //-- filename of currently opened project. When no project is opened,
    //   or when current project doesn't yet have a filename, it is an empty
    //   string.
    QString proj_filename;

    //TODO: remove (not used)
    EventVisitor_Handle htevent_visitor_handle;

    //-- instance of main window
    std::unique_ptr<MainWindow>  p_main_window;



    /*
     * String keys for xml settings file (used when working with `p_sett`)
     */

    static const QString SETT_KEY__APPL;
    static const QString SETT_KEY__APPL__LAST_PROJECT_FILENAME;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * Close currently opened project. If no project is opened,
     * this method has no effect
     */
    void closeProject();

    /**
     * Open project from XML file
     */
    void openProject(QString filename);

    /**
     * Save project to XML file
     */
    void saveProject(QString filename = "");

    /**
     * Returns pointer to settings instance
     */
    std::shared_ptr<XmlSettings> settings() const { return p_sett; };

    /**
     * Returns filename of the currently opened project. If no project is opened,
     * an empty string is returned.
     */
    QString getProjectFilename() const;

    /**
     * Returns filename of the last project that was successfully opened.
     * (this value is persisted across multpile application invocations:
     * it is saved in settings)
     */
    QString getLastProjectFilename() const;

private:

    void initSettings();
    void cryEventSys(HTCore::EventSys::Level level, QString text);
    void rememberProjectFilename(QString filename);



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
private slots:

    //void onEvent(const std::shared_ptr<Event> &);
    void onNewDataRaw(std::shared_ptr<HTCore::EventDataRaw> p_event);
    void onNewDataMsg(std::shared_ptr<HTCore::EventDataMsg> p_event);
    //void onHandlerNameChanged(const ReqHandler *p_handler, const QString &name);


signals:
    /**
     * Emitted when `EventDataRaw` happened
     */
    void eventDataRaw(std::shared_ptr<HTCore::EventDataRaw> p_event);

    /**
     * Emitted when `EventDataMsg` happened
     */
    void eventDataMsg(std::shared_ptr<HTCore::EventDataMsg> p_event);

    /**
     * Emitted when `EventSys` happened
     */
    void eventSys(std::shared_ptr<HTCore::EventSys> p_event);

    /**
     * Emitted just after project has been opened
     */
    void projectOpened(std::shared_ptr<HTCore::Project> p_project);

    /**
     * Emitted just before closing the current project
     */
    void projectBeforeClose(std::shared_ptr<HTCore::Project> p_project);

    /**
     * Emitted when title of some request handler has changed.
     * This signal is just forwarded from `#HTCore`.
     *
     * @param p_handler
     *      handler whose title has changed
     * @param name
     *      new title
     */
    void reqHandlerTitleChanged(
            const HTCore::ReqHandler *p_handler,
            const QString &name
            );
};


#endif // _APPL_H
