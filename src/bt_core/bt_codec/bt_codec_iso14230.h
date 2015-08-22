/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_ISO14230_H
#define _BT_CODEC_ISO14230_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>
#include <vector>

#include <QObject>

#include "bt_datamsg.h"
#include "bt_codec.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class Codec_ISO14230;
}

/**
 * Implementation of `#BTCore::Codec` for ISO 14230 standard.
 */
class BTCore::Codec_ISO14230 : public BTCore::Codec
{
Q_OBJECT

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    /**
     * @param own_addr
     *      see details about own, or local, address: `#setOwnAddr()`
     * @param remote_addr
     *      see details about remote address: `#setRemoteAddr()`
     */
    explicit Codec_ISO14230(uint8_t own_addr, uint8_t remote_addr);


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/

private:
    //-- Rx message that is being received at the moment. It may already be
    //   a ready message, or it may be received just partially.
    //   When message is received completely,
    //   `#BTCore::Codec::messageDecoded()` signal is emitted.
    DataMsg cur_rx_msg;

    //-- current state of ragel state machine
    int ragel_cs;

    //-- length that is specified in the header of the message. So, it is
    //   the length of the message payload data.
    int rx_user_data_len;

    //-- size of user data that is already received. While receiving data,
    //   it is compared against `rx_user_data_len`, when they become equal,
    //   that means that all payload data is received, and we need to get
    //   checksum.
    int rx_user_data_got_len;

    //-- currently calculated checksum, it is altered at each received byte.
    //   When message is received, it is compared against the received checksum
    //   byte.
    uint8_t rx_checksum;

    //-- used as target for decoded messages, and source for encoded messages
    uint8_t own_addr;
    //-- used as source for decoded messages, and target for encoded messages
    uint8_t remote_addr;

    //-- Current raw data.
    //   When new raw data arrives, it is added at the end.
    //
    //   When message is successfully decoded, its data
    //   is removed from the beginning.
    //
    //   When message parsing error happens, one byte
    //   is removed from the beginning.
    std::vector<unsigned char> raw_data;

    //-- Current index in `raw_data`
    size_t cur_raw_data_idx;


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
    virtual void accept(CodecVisitor &visitor) override;



    /**
     * Set own, or local, address. It is used as target address for Rx messages,
     * and source address for Tx messages.
     */
    void setOwnAddr(uint8_t own_addr);

    /**
     * Set remote address. It is used as target address for Tx messages,
     * and source address for Rx messages.
     */
    void setRemoteAddr(uint8_t remote_addr);

    /**
     * Get own, or local, address. See comments for `setOwnAddr()` for some details.
     */
    uint8_t getOwnAddr() const;

    /**
     * Get remote address. See comments for `setRemoteAddr()` for some details.
     */
    uint8_t getRemoteAddr() const;


private:

    void msgReset();



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:
    //NOTE: we should NOT define signals in subclasses,
    //      since if we do, then function pointer-based
    //      connect() syntax will not generate any errors,
    //      but it will just not work silently.
    //
    //void messageDecoded(const DataMsg &msg);

};


#endif // _BT_CODEC_ISO14230_H
