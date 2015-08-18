/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>
#include <QtQml>
#include <QJSEngine>
#include <QJSValue>

#include <iostream>

#include "htproject.h"
#include "htevent_data_raw.h"
#include "htevent_data_msg.h"

#include "my_util.h"

#include "bytearr_read.h"
#include "bytearr_read_write.h"


using namespace HTCore;
using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Project::Project(
        std::shared_ptr<Codec> p_codec,
        std::shared_ptr<IODev> p_io_dev
        ) :
    p_engine(std::make_shared<QJSEngine>()),
    p_codec(p_codec),
    p_io_dev(p_io_dev),
    handlers(),
    script_ctx_jsval(p_engine->evaluate("({})"))
{
    //TODO: comment these registrations
    //
    //   It seems, we register ByteArrRead as non-instantiable type,
    //   and ByteArrReadWrite as instantiable
    qmlRegisterType<ByteArrRead>     ();
    qmlRegisterType<ByteArrReadWrite>("", 1, 0, "ByteArrReadWrite");

    connect(
            p_io_dev.get(), &IODev::readyRead,
            this, &Project::onDataSrcReadyRead
           );

    connect(
            p_codec.get(), &Codec::messageDecoded,
            this, &Project::onMessageDecoded
           );

    addHandler(
            make_shared<ReqHandler>(
                "handler 1",
                p_engine,
                "(function(inputMsg, outputArr){\n"
                "     var inputArr = inputMsg.byteArr;\n"
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

    addHandler(
            make_shared<ReqHandler>(
                "handler 2",
                p_engine,
                "(function(inputMsg, outputArr){ \n"
                "     var inputArr = inputMsg.byteArr;\n"
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

    addHandler(
            make_shared<ReqHandler>(
                "handler 3",
                p_engine,
                "(function(inputMsg, outputArr){ \n"
                "     var inputArr = inputMsg.byteArr;\n"
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

void Project::addHandler(std::shared_ptr<ReqHandler> p_handler)
{
    handlers.push_back(p_handler);
    connect(
            p_handler.get(), &ReqHandler::nameChanged,
            this, &Project::onReqHandlerNameChanged
           );
}


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

    //-- create an object that will be given to handlers as input message
    QJSValue input_msg_jsval = p_engine->newObject();

    //-- actual input byte array
    ByteArrRead ba_in {*p_req_data};
    QJSValue ba_in_jsval = p_engine->newQObject(&ba_in);
    QQmlEngine::setObjectOwnership(&ba_in, QQmlEngine::CppOwnership);

    input_msg_jsval.setProperty("byteArr", ba_in_jsval);

    for (auto p_req_handler : handlers){

        ReqHandler::Result res = p_req_handler->handle(
                input_msg_jsval,
                script_ctx_jsval
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

void Project::onReqHandlerNameChanged(const QString &name)
{
    ReqHandler *p_handler = dynamic_cast<ReqHandler *>(sender());
    emit reqHandlerNameChanged(p_handler, name);
}



/* protected    */

/* public       */


