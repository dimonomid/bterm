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

#include <QObject>

#include "htdatamsg.h"
#include "htcodec.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

class HTCodec_ISO14230 : public HTCodec
{
   Q_OBJECT

   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit HTCodec_ISO14230(uint8_t own_addr, uint8_t remote_addr);

   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/

private:
   HTDataMsg cur_rx_msg;
   int ragel_cs;
   int rx_user_data_len;
   int rx_user_data_got_len;
   uint8_t rx_checksum;

   //-- used as target for decoded messages, and source for encoded messages
   uint8_t own_addr;
   //-- used as source for decoded messages, and target for encoded messages
   uint8_t remote_addr;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:
   virtual void                  addRawRxData   (const vector<uint8_t> &data) override;
   virtual void                  clearRawRxData () override;

   virtual HTDataMsg             encodeMessage  (const vector<uint8_t> &data) const override;



   void                  setOwnAddr(uint8_t own_addr);
   void                  setRemoteAddr(uint8_t remote_addr);


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/
signals:
   void messageDecoded(const HTDataMsg &msg);

};


#endif // _HTCODEC_ISO14230_H
