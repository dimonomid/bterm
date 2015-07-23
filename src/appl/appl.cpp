/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <memory>



#include "appl.h"

#include "htcodec.h"
#include "htcodec_iso14230.h"

#include "htiodev.h"
#include "htiodev_dbg.h"

#include "htdatamsg.h"

//#include "htevent_data_raw.h"
//#include "htevent_data_msg.h"


/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Appl::Appl() :
   p_codec(nullptr),
   p_io_dev(nullptr),
   p_htcore(nullptr),
   htevent_visitor_handle(*this),
   p_main_window(std::unique_ptr<MainWindow>(new MainWindow(*this)))
{

   p_io_dev = std::make_shared<HTIODevDbg>();
   p_codec = std::make_shared<HTCodec_ISO14230>(0x01, 0x02);

   p_htcore = std::unique_ptr<HTCore>{
      new HTCore{p_codec, p_io_dev}
   };

   p_events_data_raw = std::unique_ptr<HTEventsAcc<HTEventDataRaw>>{
      new HTEventsAcc<HTEventDataRaw>(1000/*TODO: settings*/)
   };

   p_events_data_msg = std::unique_ptr<HTEventsAcc<HTEventDataMsg>>{
      new HTEventsAcc<HTEventDataMsg>(1000/*TODO: settings*/)
   };



   connect(
         p_htcore.get(), &HTCore::eventDataRaw,
         this, &Appl::onNewDataRaw
         );

   connect(
         p_htcore.get(), &HTCore::eventDataMsg,
         this, &Appl::onNewDataMsg
         );



   this->p_main_window->show();

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

/* protected    */

/* public       */

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

#if 0
void Appl::onHTEvent(const std::shared_ptr<HTEvent> &p_event)
{
   p_event->accept(htevent_visitor_handle);
}
#endif

void Appl::onNewDataRaw(std::shared_ptr<HTEventDataRaw> p_event)
{
   p_events_data_raw->addEvent(p_event);

   emit eventDataRaw(p_event);
}

void Appl::onNewDataMsg(std::shared_ptr<HTEventDataMsg> p_event)
{
   p_events_data_msg->addEvent(p_event);

   emit eventDataMsg(p_event);
}





#if 0
void Appl::onNewDataRaw(const std::vector<uint8_t> &data)
{
   //TODO
}

void Appl::onNewDataMsg(const HTDataMsg &msg)
{
   //TODO
}
#endif

/* protected    */

/* public       */


