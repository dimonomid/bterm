/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>
#include <QScriptEngine>
#include <QScriptValue>

#include <iostream>

#include "htproject.h"
#include "htevent_data_raw.h"
#include "htevent_data_msg.h"

#include "my_util.h"

#include "bytearr_read.h"


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
   handlers(),
   script_ctx(p_engine->evaluate("({})"))
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
            "        outputArr.putU16(1, 0x1234);"
            "        outputArr.putU16(5, 0x1234, LITTLE_END);"
            "        outputArr.putU16(10, 0x1234, BIG_END);"
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

   auto p_event = std::make_shared<EventDataMsg>(msg, EventDataMsg::Direction::RX);
   emit (eventDataMsg(p_event));

   std::shared_ptr<std::vector<uint8_t>> p_req_data = msg.getUserData();

   for (auto req_handler : handlers){

      ReqHandler::Result res = req_handler.handle(
            *p_req_data,
            script_ctx
            );


#if 0
      qDebug() << "handler: " << req_handler.getName();
#endif

      switch (res){
         case ReqHandler::Result::UNKNOWN:
            qDebug("unknown result: should never be here");
            break;

         case ReqHandler::Result::OK_NOT_HANDLED:
#if 0
            qDebug() << "not handled";
#endif
            break;

         case ReqHandler::Result::OK_HANDLED:
            {
               auto p_data_tx = req_handler.getResponse();
               DataMsg msg_tx = p_codec->encodeMessage(*p_data_tx);
               auto p_data_raw_tx = msg_tx.getRawData();
               p_io_dev->write(*p_data_raw_tx);

               auto p_event = std::make_shared<EventDataMsg>(msg_tx, EventDataMsg::Direction::TX);
               emit (eventDataMsg(p_event));
            }
#if 0
            qDebug() << "handled, response: " << MyUtil::byteArrayToHex(
                  *req_handler.getResponse()
                  );
#endif
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


