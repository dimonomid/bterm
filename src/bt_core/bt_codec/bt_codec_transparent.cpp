/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec_transparent.h"
#include "bt_codec_visitor.h"



using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

CodecTransparent::CodecTransparent(CodecIdx codec_idx) :
    Codec(codec_idx)
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

void CodecTransparent::addRawRxData(const std::vector<uint8_t> &data)
{
    emit messageDecoded( encodeMessage(data) );
}

void CodecTransparent::clearRawRxData()
{
}

DataMsg CodecTransparent::encodeMessage(const std::vector<uint8_t> &data) const
{
    DataMsg msg {};
    msg.addData(DataPart::DataType::USER, data);
    return msg;
}

std::vector<std::shared_ptr<ReqHandler>> CodecTransparent::getStdHandlers() const
{
    //-- just return empty vector
    return std::vector<std::shared_ptr<ReqHandler>>{};
}


void CodecTransparent::accept(CodecVisitor &visitor)
{
    visitor.visit(*this);
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


