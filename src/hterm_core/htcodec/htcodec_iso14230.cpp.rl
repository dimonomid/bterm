/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htcodec_iso14230.h"


/*******************************************************************************
 * AUTO-GENERATED RAGEL DATA
 ******************************************************************************/

%%{
   machine iso14230;
   alphtype unsigned char;
   write data;
}%%

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HTCodec_ISO14230::HTCodec_ISO14230() :
   cur_rx_msg(HTDataMsg()),
   ragel_cs(0)
{
   this->clearRawRxData();
}





/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


/*******************************************************************************
 * AUTO-GENERATED RAGEL CODE
 ******************************************************************************/

%%{
   action message_reset {
      /* TODO */
   }

   action got_fmt_with_len {
      rx_user_data_len = fc & ~0x80;
   }

   action got_separate_len {
      rx_user_data_len = fc;
   }

   action got_tgt {
      //tgt = fc;
      //TODO
   }

   action got_src {
      //src = fc;
      //TODO
   }

   action got_service_byte {
      this->cur_rx_msg.addData(HTDataPart::Type::SERVICE, fc);
   }

   action got_data_byte {
      this->cur_rx_msg.addData(HTDataPart::Type::USER, fc);
   }

   action message_received {
      /* TODO */
   }

   action message_error {
      /* TODO */
      fhold; fgoto msg_start;
   }






   action is_tgt_valid {
      //(!tgt_care || fc == tgt_needed);
      //TODO
      1
   }

   action is_src_valid {
      //(!src_care || fc == src_needed);
      //TODO
      1
   }

   action is_waiting_for_data {
      (rx_user_data_got_len++ < rx_user_data_len)
   }

   action is_checksum_correct {
      1/*TODO*/
   }






   fmt_with_len = (0x81..0xff);
   fmt_separate_len = (0x80 any);
   tgt = (any);
   src = (any);
   data = (any);
   checksum = (any);

   message = 
      (
       (fmt_with_len @got_fmt_with_len | fmt_separate_len @got_separate_len) $got_service_byte
       (tgt        when is_tgt_valid          @got_tgt       ) $got_service_byte
       (src        when is_src_valid          @got_src       ) $got_service_byte
       (data       when is_waiting_for_data   @got_data_byte )*
       <:
       (checksum   when is_checksum_correct   @message_received) $got_service_byte
      ) >to(message_reset) $err(message_error)
      ;

main := (msg_start: message)*;

}%%

/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */

void HTCodec_ISO14230::addRawRxData(const vector<unsigned char> &data)
{
   const unsigned char *p = data.data();
   const unsigned char *pe = p + data.size();
   int cs = this->ragel_cs;
   const unsigned char *eof = nullptr;
   %%{
      write exec;
   }%%
   ragel_cs = cs;
}

void HTCodec_ISO14230::clearRawRxData()
{
   this->cur_rx_msg.clear();

   {
      int cs = ragel_cs;
      %%{
         write init;
      }%%
      ragel_cs = cs;
   }
}

vector<unsigned char> HTCodec_ISO14230::encodeMessage(const vector<unsigned char> &data)
{
   return vector<unsigned char>();
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


