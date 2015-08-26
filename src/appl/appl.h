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

#include "bt_project.h"
#include "bt_events_acc.h"
#include "bt_iodev.h"
#include "bt_codec.h"
#include "bt_event_sys.h"

#include "bt_event_visitor__appl_handle.h"




class XmlSettings;
class IODevSerial;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

/**
 * Class that essentially provides a "glue" for two other application parties:
 * `#BTCore` and GUI.
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

    friend EventVisitor_ApplHandle;


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
    std::shared_ptr<IODevSerial> p_io_dev;

    //-- current project
    std::shared_ptr<BTCore::Project> p_project;

    //-- accumulator of data raw events
    //   (NOTE: accessed by EventVisitor_ApplHandle)
    std::unique_ptr<BTCore::EventsAcc<BTCore::EventDataRaw>> p_events_data_raw;

    //-- accumulator of data message events
    //   (NOTE: accessed by EventVisitor_ApplHandle)
    std::unique_ptr<BTCore::EventsAcc<BTCore::EventDataMsg>> p_events_data_msg;

    //-- filename of currently opened project. When no project is opened,
    //   or when current project doesn't yet have a filename, it is an empty
    //   string.
    QString proj_filename;

    EventVisitor_ApplHandle bt_event_visitor__appl_handle;

    //-- instance of main window
    std::unique_ptr<MainWindow>  p_main_window;



    /****************************************************************************
     * STATIC DATA
     ***************************************************************************/

private:
    /*
     * String keys for xml settings file (used when working with `p_sett`)
     */

    static const QString SETT_KEY__APPL;
    static const QString SETT_KEY__APPL__LAST_PROJECT_FILENAME;
    static const QString SETT_KEY__APPL__IO;
    static const QString SETT_KEY__APPL__IO__PORT_NAME;


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
     * Create new project. Currently opened project (if any) will
     * be closed.
     */
    void newProject();

    /**
     * Open project from XML file. Currently opened project (if any) will
     * be closed.
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

    /**
     * Returns IO port name, like "/dev/ttyUSB0" on linux, or "COM1" on Windows
     */
    QString getIOPortName() const;

    /**
     * Set IO port name, like "/dev/ttyUSB0" on linux, or "COM1" on Windows.
     *
     * @return `true` if setting was successful, `false` otherwise.
     */
    bool setIOPortName(QString port_name);

    /**
     * Returns whether IO device is currently opened
     */
    bool isIODevOpened() const;



private:

    void initSettings();
    void cryEventSys(BTCore::MsgLevel level, QString text);
    void rememberProjectFilename(QString filename);
    void connectToCurProject();



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
private slots:

    void onEvent(std::shared_ptr<BTCore::Event> p_event);
    void onIODevOpenStatusChanged(bool opened);
    void onIODevError(QString error_msg);

signals:

    /**
     * Emitted when some event has happened (it is typically forwarded
     * from `BTCore`)
     */
    void event(std::shared_ptr<BTCore::Event> p_event);

    /**
     * Emitted just after project has been opened
     */
    void projectOpened(QString proj_filename, std::shared_ptr<BTCore::Project> p_project);

    /**
     * Emitted just after project has been saved
     */
    void projectSaved(QString proj_filename, std::shared_ptr<BTCore::Project> p_project);

    /**
     * Emitted just before closing the current project
     */
    void projectBeforeClose(std::shared_ptr<BTCore::Project> p_project);

    /**
     * Emitted when IODev gets opened or closed
     */
    void ioDevOpenStatusChanged(bool opened);

};


#endif // _APPL_H
