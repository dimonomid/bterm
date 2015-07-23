/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include <iostream>

#include "htproject.h"
#include "htevent_data_raw.h"
#include "htevent_data_msg.h"


using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Project::Project(
      std::shared_ptr<Codec> p_codec,
      std::shared_ptr<IODev> p_io_dev
      ) :
   p_codec(p_codec),
   p_io_dev(p_io_dev)
{

   connect(
         p_io_dev.get(), &IODev::readyRead,
         this, &Project::onDataSrcReadyRead
         );

   connect(
         p_codec.get(), &Codec::messageDecoded,
         this, &Project::onMessageDecoded
         );

}

Project::~Project()
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

void Project::onDataSrcReadyRead(int bytes_available)
{
   std::ignore = bytes_available;

   //-- get received data
   std::vector<uint8_t> data = p_io_dev->read();

   auto p_event = std::make_shared<EventDataRaw>(data);
   emit (eventDataRaw(p_event));

#if 0
   for (auto byte : data){
      qDebug(byte + " ");
   }
#endif

   //-- feed received data as a raw data to codec
   p_codec->addRawRxData( data );
}

void Project::onMessageDecoded(const DataMsg &msg)
{
   //qDebug(msg.toString().c_str());

   auto p_event = std::make_shared<EventDataMsg>(msg);
   emit (eventDataMsg(p_event));

   //TODO: handle response rules, generate response if necessary
}



/* protected    */

/* public       */


