/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>
#include <QJSEngine>
#include <QJSValue>

#include <iostream>

#include "htproject.h"
#include "htevent_data_raw.h"
#include "htevent_data_msg.h"

#include "my_util.h"

#include "bytearr_read.h"


using namespace HTCore;
using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Project::Project(
      std::shared_ptr<Codec> p_codec,
      std::shared_ptr<IODev> p_io_dev
      ) :
   p_codec(p_codec),
   p_io_dev(p_io_dev),
   p_engine(std::make_shared<QJSEngine>()),
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
         make_shared<ReqHandler>(
            "handler 1",
            p_engine,
            "(function(inputArr, outputArr){\n"
            "     var handled = false;\n"

            "     if (inputArr.getU08(0) === 0x03){\n"
            "        outputArr.putU08(1, 0x04);\n"
            "        handled = true;\n"
            "     };\n"

            "     return {\n"
            "        handled: handled\n"
            "     };\n"
            " })\n"
            )
         );

   handlers.push_back(
         make_shared<ReqHandler>(
            "handler 2",
            p_engine,
            "(function(inputArr, outputArr){ \n"
            "     var handled = false;\n"

            "     if (inputArr.getU08(0) === 0x04){\n"
            "        outputArr.putU16(1, 0x1234);\n"
            "        outputArr.putU16(5, 0x1234, LITTLE_END);\n"
            "        outputArr.putU16(10, 0x1234, BIG_END);\n"
            "        handled = true;\n"
            "     };\n"

            "     return {\n"
            "        handled: handled\n"
            "     };\n"
            " })\n"
            )
         );

   handlers.push_back(
         make_shared<ReqHandler>(
            "handler 3",
            p_engine,
            "(function(inputArr, outputArr){ \n"
            "     var handled = false;\n"

            "     if (inputArr.getU08(0) === 0x04){\n"
            "        outputArr.putU08(1, 0xff);\n"
            "        handled = true;\n"
            "     };\n"

            "     return {\n"
            "        handled: handled\n"
            "     };\n"
            " })\n"
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

std::shared_ptr<ReqHandler> Project::getHandler(size_t index)
{
   return handlers[index];
}

size_t Project::getHandlersCnt() const
{
   return handlers.size();
}


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

   for (auto p_req_handler : handlers){

      ReqHandler::Result res = p_req_handler->handle(
            *p_req_data,
            script_ctx
            );


#if 0
      qDebug() << "handler: " << p_req_handler->getName();
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
               auto p_data_tx = p_req_handler->getResponse();
               DataMsg msg_tx = p_codec->encodeMessage(*p_data_tx);
               auto p_data_raw_tx = msg_tx.getRawData();
               p_io_dev->write(*p_data_raw_tx);

               auto p_event = std::make_shared<EventDataMsg>(msg_tx, EventDataMsg::Direction::TX);
               emit (eventDataMsg(p_event));
            }
#if 0
            qDebug() << "handled, response: " << MyUtil::byteArrayToHex(
                  *p_req_handler->getResponse()
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


