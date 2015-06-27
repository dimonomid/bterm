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

#include "htdatasrc.h"
#include "htdatasrc_dbg.h"

#include "htdatamsg.h"



/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Appl::Appl() :
   p_codec(nullptr),
   p_data_src(nullptr),
   p_htcore(nullptr),
   htevent_visitor_handle(*this),
   main_window()
{

   p_data_src = std::make_shared<HTDataSrcDbg>();
   p_codec = std::make_shared<HTCodec_ISO14230>(0x01, 0x02);

   p_htcore = std::unique_ptr<HTCore>{
      new HTCore{p_codec, p_data_src}
   };

   //-- connect HTCore's events to onHTEvent() handler, in which we 
   //   use visitor
   connect(
         p_htcore.get(), SIGNAL(event(const std::shared_ptr<HTEvent> &)),
         this, SLOT(onHTEvent(const std::shared_ptr<HTEvent> &))
         );

   //-- connect separate visitor's events to our slots
   connect(
         &htevent_visitor_handle, SIGNAL(newDataRaw(const std::vector<uint8_t> &)),
         this, SLOT(onNewDataRaw(const std::vector<uint8_t> &))
         );

   connect(
         &htevent_visitor_handle, SIGNAL(newDataMsg(const HTDataMsg &)),
         this, SLOT(onNewDataMsg(const HTDataMsg &))
         );

   //-- connect separate visitor's events to mainwindow's slots
   connect(
         &htevent_visitor_handle, SIGNAL(newDataRaw(const std::vector<uint8_t> &)),
         &main_window, SLOT(onNewDataRaw(const std::vector<uint8_t> &))
         );

   connect(
         &htevent_visitor_handle, SIGNAL(newDataMsg(const HTDataMsg &)),
         &main_window, SLOT(onNewDataMsg(const HTDataMsg &))
         );

   this->main_window.show();

}

Appl::~Appl()
{
   disconnect(
         p_htcore.get(), SIGNAL(event(const std::shared_ptr<HTEvent> &)),
         this, SLOT(onHTEvent(const std::shared_ptr<HTEvent> &))
         );
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

void Appl::onHTEvent(const std::shared_ptr<HTEvent> &p_event)
{
   p_event->accept(htevent_visitor_handle);
}

void Appl::onNewDataRaw(const std::vector<uint8_t> &data)
{
   //TODO
}

void Appl::onNewDataMsg(const HTDataMsg &msg)
{
   //TODO
}

/* protected    */

/* public       */


