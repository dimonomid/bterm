/*******************************************************************************
 *   Description:   TODO
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

    std::shared_ptr<XmlSettings> p_sett;
    std::shared_ptr<HTCore::Codec> p_codec;
    std::shared_ptr<HTCore::IODev> p_io_dev;
    std::shared_ptr<HTCore::Project> p_project;
    std::unique_ptr<HTCore::EventsAcc<HTCore::EventDataRaw>> p_events_data_raw;
    std::unique_ptr<HTCore::EventsAcc<HTCore::EventDataMsg>> p_events_data_msg;

    QString proj_filename;

    EventVisitor_Handle htevent_visitor_handle;

    std::unique_ptr<MainWindow>  p_main_window;



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
     * Open project from XML file
     */
    void openProject(QString filename);

    /**
     * Save project to XML file
     */
    void saveProject(QString filename);

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



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
private slots:

    //void onEvent(const std::shared_ptr<Event> &);
    void onNewDataRaw(std::shared_ptr<HTCore::EventDataRaw> p_event);
void onNewDataMsg(std::shared_ptr<HTCore::EventDataMsg> p_event);
//void onHandlerNameChanged(const ReqHandler *p_handler, const QString &name);


signals:
    void eventDataRaw(std::shared_ptr<HTCore::EventDataRaw> p_event);
    void eventDataMsg(std::shared_ptr<HTCore::EventDataMsg> p_event);
    void eventSys(std::shared_ptr<HTCore::EventSys> p_event);

    /**
     * Emitted just after project has been opened
     */
    void projectOpened(std::shared_ptr<HTCore::Project> p_project);

    void reqHandlerNameChanged(
            const HTCore::ReqHandler *p_handler,
            const QString &name
            );
};


#endif // _APPL_H
