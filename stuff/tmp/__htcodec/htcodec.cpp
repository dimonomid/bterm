/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QJSEngine>

#include "bt_codec.h"
#include "my_util.h"
#include "bt_bytearr_read.h"


using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Codec::Codec(
        std::shared_ptr<QJSEngine> p_engine
        ) :
    p_engine(p_engine),
    codec_js()
{
    //TODO: filename from config
    QString codec_js_code = MyUtil::readFile(
            "/home/dimon/projects/bterm/bterm/src/bt_core/bt_codec/codec_iso14230.js"
            );

    codec_js = p_engine->evaluate(codec_js_code);
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

void Codec::addRawRxData(const std::vector<uint8_t> &data)
{
    ByteArrRead *p_ba_data = new ByteArrRead(data);
    codec_js.property("feedRawData").call(
            QJSValueList() << p_engine->newQObject(p_ba_data)
            );
}

void Codec::clearRawRxData()
{
    //TODO
}

DataMsg Codec::encodeMessage(const std::vector<uint8_t> &data) const
{
    //TODO
    DataMsg ret{};
    return ret;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


