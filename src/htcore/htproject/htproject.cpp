/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>
#include <QScriptEngine>

#include <iostream>

#include "htproject.h"
#include "htevent_data_raw.h"
#include "htevent_data_msg.h"

#include "my_util.h"


using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Project::Project(
      std::shared_ptr<Codec> p_codec,
      std::shared_ptr<IODev> p_io_dev
      ) :
   p_codec(p_codec),
   p_io_dev(p_io_dev),
   p_engine(std::make_shared<QScriptEngine>()),
   handlers()
{

   connect(
         p_io_dev.get(), &IODev::readyRead,
         this, &Project::onDataSrcReadyRead
         );

   connect(
         p_codec.get(), &Codec::messageDecoded,
         this, &Project::onMessageDecoded
         );

   handlers.push_back(
         ReqHandler(
            "handler 1",
            p_engine,
            "(function(inputArr, outputArr){ "
            "     var handled = false;"

            "     if (inputArr.getU08(0) === 0x03){"
            "        outputArr.putU08(1, 0x04);"
            "        handled = true;"
            "     };"

            "     return {"
            "        handled: handled"
            "     };"
            " })"
            )
         );

   handlers.push_back(
         ReqHandler(
            "handler 2",
            p_engine,
            "(function(inputArr, outputArr){ "
            "     var handled = false;"

            "     if (inputArr.getU08(0) === 0x04){"
            "        outputArr.putU08(1, 0xaa);"
            "        handled = true;"
            "     };"

            "     return {"
            "        handled: handled"
            "     };"
            " })"
            )
         );

   handlers.push_back(
         ReqHandler(
            "handler 3",
            p_engine,
            "(function(inputArr, outputArr){ "
            "     var handled = false;"

            "     if (inputArr.getU08(0) === 0x04){"
            "        outputArr.putU08(1, 0xff);"
            "        handled = true;"
            "     };"

            "     return {"
            "        handled: handled"
            "     };"
            " })"
            )
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

   std::shared_ptr<std::vector<uint8_t>> p_req_data = msg.getUserData();

   QScriptValue chain_data = p_engine->evaluate("({})");

   for (auto req_handler : handlers){
      ReqHandler::Result res = req_handler.handle(
            p_req_data,
            chain_data
            );


      qDebug() << "handler: " << req_handler.getName();

      switch (res){
         case ReqHandler::Result::UNKNOWN:
            qDebug("unknown result: should never be here");
            break;

         case ReqHandler::Result::OK_NOT_HANDLED:
            qDebug() << "not handled";
            break;

         case ReqHandler::Result::OK_HANDLED:
            qDebug() << "handled, response: " << MyUtil::byteArrayToHex(
                  *req_handler.getResponse()
                  );
            break;

         case ReqHandler::Result::ERROR:
            qDebug() << "error";
            break;
      }

      if (res == ReqHandler::Result::OK_HANDLED){
         break;
      }
   }


   //TODO: handle response rules, generate response if necessary
}



/* protected    */

/* public       */


