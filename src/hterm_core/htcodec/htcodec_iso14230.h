/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTCODEC_ISO14230_H
#define _HTCODEC_ISO14230_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

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
   explicit HTCodec_ISO14230(unsigned char own_addr, unsigned char remote_addr);

   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/

private:
   HTDataMsg cur_rx_msg;
   int ragel_cs;
   int rx_user_data_len;
   int rx_user_data_got_len;
   unsigned char rx_checksum;

   //-- used as target for decoded messages, and source for encoded messages
   unsigned char own_addr;
   //-- used as source for decoded messages, and target for encoded messages
   unsigned char remote_addr;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:
   virtual void                  addRawRxData   (const vector<unsigned char> &data) override;
   virtual void                  clearRawRxData () override;

   virtual vector<unsigned char> encodeMessage  (const vector<unsigned char> &data) const override;



   void                  setOwnAddr(unsigned char own_addr);
   void                  setRemoteAddr(unsigned char remote_addr);


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/
signals:
   void messageDecoded(const HTDataMsg &msg);

};


#endif // _HTCODEC_ISO14230_H
