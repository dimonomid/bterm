/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTCODEC_ISO14230_H
#define _HTCODEC_ISO14230_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>
#include <vector>

#include <QObject>

#include "htdatamsg.h"
#include "htcodec.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class Codec_ISO14230;
}

class HTCore::Codec_ISO14230 : public HTCore::Codec
{
Q_OBJECT

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    explicit Codec_ISO14230(uint8_t own_addr, uint8_t remote_addr);

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/

private:
    DataMsg cur_rx_msg;
    int ragel_cs;
    int rx_user_data_len;
    int rx_user_data_got_len;
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
    size_t cur_raw_data_idx;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:
    virtual void                  addRawRxData   (const std::vector<uint8_t> &data) override;
    virtual void                  clearRawRxData () override;

    virtual DataMsg             encodeMessage  (const std::vector<uint8_t> &data) const override;
    virtual void      accept(CodecVisitor &visitor) override;



    void                  setOwnAddr(uint8_t own_addr);
    void                  setRemoteAddr(uint8_t remote_addr);

    uint8_t               getOwnAddr() const;
    uint8_t               getRemoteAddr() const;


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


#endif // _HTCODEC_ISO14230_H
