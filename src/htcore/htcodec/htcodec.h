/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HTCODEC_H
#define _HTCODEC_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>

#include <QObject>
#include "htdatamsg.h"

#include <vector>


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class Codec;
    class CodecVisitor;
}

/**
 * Abstract codec that is used by `#HTCore::Project` to decode messages
 * (`#DataMsg`) from raw Rx data, and encode Tx messages.
 */
class HTCore::Codec : public QObject
{
Q_OBJECT

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

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
     * Accept codec visitor.
     *
     * (if you're unfamiliar with visitor pattern, read about it somewhere; for
     * example, on Wikipedia: https://en.wikipedia.org/wiki/Visitor_pattern )
     */
    virtual void accept(CodecVisitor &visitor) = 0;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:

    /**
     * Emitted when new Rx message was decoded from raw data.
     */
    void messageDecoded(const DataMsg &msg);

};


#endif // _HTCODEC_H
