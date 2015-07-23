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

#include "htevent_visitor_handle.h"


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

   std::shared_ptr<HTCore::Codec> p_codec;
   std::shared_ptr<HTCore::IODev> p_io_dev;
   std::unique_ptr<HTCore::Project> p_project;
   std::unique_ptr<HTCore::EventsAcc<HTCore::EventDataRaw>> p_events_data_raw;
   std::unique_ptr<HTCore::EventsAcc<HTCore::EventDataMsg>> p_events_data_msg;

   EventVisitor_Handle htevent_visitor_handle;

   std::unique_ptr<MainWindow>  p_main_window;



   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/

   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/
private slots:

   //void onEvent(const std::shared_ptr<Event> &);
   void onNewDataRaw(std::shared_ptr<HTCore::EventDataRaw> p_event);
   void onNewDataMsg(std::shared_ptr<HTCore::EventDataMsg> p_event);


signals:
   void eventDataRaw(std::shared_ptr<HTCore::EventDataRaw> p_event);
   void eventDataMsg(std::shared_ptr<HTCore::EventDataMsg> p_event);

};


#endif // _APPL_H
