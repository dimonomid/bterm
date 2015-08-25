/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_H
#define _BT_CODEC_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>

#include <QObject>
#include "bt_datamsg.h"
#include "bt_codec_types.h"

#include <vector>


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class Codec;
    class CodecVisitor;
    class ReqHandler;
}

/**
 * Abstract codec that is used by `#BTCore::Project` to decode messages
 * (`#BTCore::DataMsg`) from raw Rx data, and encode Tx messages.
 *
 * See subclasses for concrete codecs implementation. It is relatively
 * easy to write your own as well.
 */
class BTCore::Codec :
    public QObject,
    public std::enable_shared_from_this<BTCore::Codec>
{
Q_OBJECT

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    Codec(CodecIdx codec_idx) :
        codec_idx(codec_idx)
    {
    }



    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    CodecIdx codec_idx;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * Get codec index (see `#BTCore::CodecIdx`)
     */
    CodecIdx getCodecIdx() const
    {
        return codec_idx;
    }

    /**
     * Add raw data to be parsed by codec
     *
     * @param data
     *      raw data to add
     */
    virtual void addRawRxData   (const std::vector<uint8_t> &data) = 0;

    /**
     * Drop any existing raw data, effectively resetting the codec Rx state
     */
    virtual void clearRawRxData () = 0;

    /**
     * Encode the message with codec. It takes plain vector of `uint8_t`, and
     * returns an instance of `DataMsg`.
     */
    virtual DataMsg encodeMessage  (const std::vector<uint8_t> &data) const = 0;

    /**
     * Returns the sequence of the codec-specific handlers, they should be
     * called after all user handlers (if no user handler have handled the
     * request)
     */
    virtual std::vector<std::shared_ptr<ReqHandler>> getStdHandlers() const = 0;

    /**
     * Accept codec visitor.
     *
     * (if you're unfamiliar with visitor pattern, read about it somewhere; for
     * example, on Wikipedia: https://en.wikipedia.org/wiki/Visitor_pattern )
     */
    virtual void accept(CodecVisitor &visitor) = 0;


    /**
     * Returns shared pointer to this instance of `Codec`
     */
    std::shared_ptr<Codec> getSharedPtr();

    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:

    /**
     * Emitted when new Rx message was decoded from raw data.
     */
    void messageDecoded(const DataMsg &msg);

    /**
     * Emitted when codec settings were changed
     * (used to mark project as dirty)
     */
    void settingsChanged();

};


#endif // _BT_CODEC_H
