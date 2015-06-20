/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htcodec_iso14230.h"

#include <iostream>


/*******************************************************************************
 * MACROS
 ******************************************************************************/

//-- I have difficulties getting QT_NO_DEBUG_OUTPUT to work (and even more,
//   it's project-wide, but I'd prefer it to be class-wide),
//   so I just use simple macro here
//#define  _DEBUG(...)    qDebug(__VA_ARGS__)
#define  _DEBUG(...)    strlen("")


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

HTCodec_ISO14230::HTCodec_ISO14230(
      unsigned char own_addr,
      unsigned char remote_addr
      ) :
   cur_rx_msg(),
   ragel_cs(0),
   rx_user_data_len(0),
   rx_user_data_got_len(0),
   own_addr(own_addr),
   remote_addr(remote_addr)
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
      _DEBUG("reset");
      this->clearRawRxData();
   }

   action got_fmt_with_len {
      rx_user_data_len = fc & ~0x80;
      _DEBUG("fmt with len=%d", (int)rx_user_data_len);
   }

   action got_separate_len {
      rx_user_data_len = fc;
      _DEBUG("separate len");
   }

   action got_tgt {
      //tgt = fc;
      //TODO
      _DEBUG("tgt");
   }

   action got_src {
      //src = fc;
      //TODO
      _DEBUG("src");
   }

   action got_service_byte {
      this->cur_rx_msg.addData(HTDataPart::Type::SERVICE, fc);
      this->rx_checksum += fc;
      _DEBUG("got service byte: 0x%x", fc);
   }

   action got_data_byte {
      this->cur_rx_msg.addData(HTDataPart::Type::USER, fc);
      this->rx_checksum += fc;
      _DEBUG("got data byte: 0x%x", fc);
   }

   action message_received {
      /* TODO */
      _DEBUG("msg received");
      emit messageDecoded(this->cur_rx_msg);
   }

   action message_error {
      /* TODO */
      _DEBUG("msg error");
      /*fhold; */fgoto msg_start;
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
      _DEBUG("waiting: rx_user_data_got_len=%d", rx_user_data_got_len),
      (rx_user_data_got_len++ < rx_user_data_len)
   }

   action is_checksum_correct {
      _DEBUG("is_checksum_correct"),
      (this->rx_checksum == fc)
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
       (checksum   when is_checksum_correct   $got_service_byte @message_received)
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
   //-- initialize variables necessary for ragel machine
   //   (it is possible to set ragel to use different variable names,
   //   but I find it more clear to just explicitly define needed variables)
   const unsigned char *p = data.data();
   const unsigned char *pe = p + data.size();
   int cs = this->ragel_cs;
   const unsigned char *eof = nullptr;

   //-- execute machine
   %%{
      write exec;
   }%%

   //-- remember ragel machine's current state
   ragel_cs = cs;
}

void HTCodec_ISO14230::clearRawRxData()
{
   this->rx_user_data_got_len = 0;
   this->rx_user_data_len = 0;
   this->rx_checksum = 0;

   this->cur_rx_msg.clear();

   {
      int cs = ragel_cs;
      %%{
         write init;
      }%%
      ragel_cs = cs;
   }
}

vector<unsigned char> HTCodec_ISO14230::encodeMessage(const vector<unsigned char> &data) const
{
   vector<unsigned char> ret{};

   //-- put length
   if (data.size() >= 0x40){
      ret.push_back(0x80);
      ret.push_back(data.size());
   } else {
      ret.push_back(0x80 | data.size());
   }

   ret.push_back(remote_addr);
   ret.push_back(own_addr);

   //-- push user data
   ret.insert(ret.end(), data.begin(), data.end());

   //-- calculate and push checksum
   {
      unsigned char checksum = 0;
      for (auto byte : ret){
         checksum += byte;
      }
      ret.push_back(checksum);
   }

   return ret;
}


void HTCodec_ISO14230::setOwnAddr(unsigned char own_addr)
{
   this->own_addr = own_addr;
}

void HTCodec_ISO14230::setRemoteAddr(unsigned char remote_addr)
{
   this->remote_addr = remote_addr;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


