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

#include "htcore.h"
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

   std::shared_ptr<HTCodec> p_codec;
   std::shared_ptr<HTIODev> p_data_src;
   std::unique_ptr<HTCore> p_htcore;
   std::unique_ptr<HTEventsAcc<HTEventDataRaw>> p_events_data_raw;
   std::unique_ptr<HTEventsAcc<HTEventDataMsg>> p_events_data_msg;

   HTEventVisitor_Handle htevent_visitor_handle;

   MainWindow main_window;



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

   //void onHTEvent(const std::shared_ptr<HTEvent> &);
   void onNewDataRaw(const std::shared_ptr<HTEventDataRaw> &p_event);
   void onNewDataMsg(const std::shared_ptr<HTEventDataMsg> &p_event);



};


#endif // _APPL_H
