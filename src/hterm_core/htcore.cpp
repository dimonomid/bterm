/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include <iostream>

#include "htcore.h"
#include "htevent_data_raw.h"
#include "htevent_data_msg.h"


/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HTCore::HTCore(
      const std::shared_ptr<HTCodec> &p_codec,
      const std::shared_ptr<HTDataSrc> &p_data_src
      ) :
   p_codec(p_codec),
   p_data_src(p_data_src)
{

   connect(
         p_data_src.get(), SIGNAL(readyRead(int)),
         this, SLOT(onDataSrcReadyRead(int))
         );

   connect(
         p_codec.get(), SIGNAL(messageDecoded(const HTDataMsg &)),
         this, SLOT(onMessageDecoded(const HTDataMsg &))
         );

}

HTCore::~HTCore()
{

   disconnect(
         p_data_src.get(), SIGNAL(readyRead(int)),
         this, SLOT(onDataSrcReadyRead(int))
         );

   disconnect(
         p_codec.get(), SIGNAL(messageDecoded(const HTDataMsg &)),
         this, SLOT(onMessageDecoded(const HTDataMsg &))
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

void HTCore::onDataSrcReadyRead(int bytes_available)
{
   std::ignore = bytes_available;

   //-- get received data
   std::vector<uint8_t> data = p_data_src->read();

   auto p_event = std::make_shared<HTEventDataRaw>(data);
   emit (event(p_event));

#if 0
   for (auto byte : data){
      qDebug(byte + " ");
   }
#endif

   //-- feed received data as a raw data to codec
   p_codec->addRawRxData( data );
}

void HTCore::onMessageDecoded(const HTDataMsg &msg)
{
   qDebug(msg.toString().c_str());

   auto p_event = std::make_shared<HTEventDataMsg>(msg);
   emit (event(p_event));
}



/* protected    */

/* public       */


