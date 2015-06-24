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
   htevent_visitor_handle(*this)
{

   p_data_src = std::make_shared<HTDataSrcDbg>();
   p_codec = std::make_shared<HTCodec_ISO14230>(0x01, 0x02);

   p_htcore = std::unique_ptr<HTCore>{
      new HTCore{p_codec, p_data_src}
   };

   connect(
         p_htcore.get(), SIGNAL(event(const std::shared_ptr<HTEvent> &)),
         this, SLOT(onHTEvent(const std::shared_ptr<HTEvent> &))
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

/* protected    */

/* public       */


