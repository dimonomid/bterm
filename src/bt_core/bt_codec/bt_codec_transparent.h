/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_TRANSPARENT_H
#define _BT_CODEC_TRANSPARENT_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include "bt_codec.h"



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class CodecTransparent;
}

/**
 * Implementation of `#BTCore::Codec` for "pseudo-codec": it doesn't actually
 * encode or decode anything, it transmits data back and forth unchanged.
 */
class BTCore::CodecTransparent : public BTCore::Codec
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    explicit CodecTransparent(CodecIdx codec_idx);


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual void addRawRxData   (const std::vector<uint8_t> &data) override;
    virtual void clearRawRxData () override;

    virtual DataMsg encodeMessage  (const std::vector<uint8_t> &data) const override;
    virtual std::vector<std::shared_ptr<ReqHandler>> getStdHandlers() const override;
    virtual void accept(CodecVisitor &visitor) override;



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_CODEC_TRANSPARENT_H
