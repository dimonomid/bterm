/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec_iso14230.h"
#include "bt_codec_visitor.h"
#include "bt_reqhandler.h"

#include <iostream>


using namespace std;
using namespace BTCore;

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

Codec_ISO14230::Codec_ISO14230(
        CodecNum codec_num
        ) :
    Codec(codec_num),
    cur_rx_msg(),
    ragel_cs(0),
    rx_user_data_len(0),
    rx_user_data_got_len(0),

    fmt_rx(0x80),
    own_addr_rx(0xff),
    remote_addr_rx(0xff),

    fmt_tx(0x80),
    own_addr_tx(0x10),
    remote_addr_tx(0xf0),

    raw_data(),
    cur_raw_data_idx(0)
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
      this->msgReset();
   }

   action got_fmt {
       if (fc > this->fmt_rx){
           //-- got fmt with len
           rx_user_data_len = fc & ~this->fmt_rx;
           _DEBUG("fmt with len=%d", (int)rx_user_data_len);
           fnext l_tgt;
       } else {
           _DEBUG("got fmt, waiting for separate len..");
       }
   }

   action got_len {
       rx_user_data_len = fc;
       _DEBUG("separate len=%d", (int)rx_user_data_len);
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
      this->cur_rx_msg.addDataByte(DataPart::DataType::SERVICE, fc);
      this->rx_checksum += fc;
      _DEBUG("got service byte: 0x%x, checksum: 0x%x", (unsigned int)fc, (unsigned int)this->rx_checksum);
   }

   action got_data_byte {
      this->cur_rx_msg.addDataByte(DataPart::DataType::USER, fc);
      this->rx_checksum += fc;
      _DEBUG("got data byte: 0x%x", fc);
   }

   action message_received {
      _DEBUG("msg received");
      del_from_beginning = p - raw_data.data() + 1;

      emit messageDecoded(this->cur_rx_msg);
   }

   action message_error {
      _DEBUG("msg error, byte: 0x%x", fc);

      //-- remove first byte
      del_from_beginning += 1;

      //-- start parsing from the next byte
      p = raw_data.data()
         + del_from_beginning
         - 1/*because it will now be incremented again*/
         ;
      /*fhold; */fgoto msg_start;
   }






   action is_fmt_valid {
       ((fc & this->fmt_rx) == this->fmt_rx)
   }

   action is_len_valid {
       1
   }

   action is_tgt_valid {
       (this->own_addr_rx == 0xff || fc == this->own_addr_rx)
   }

   action is_src_valid {
       (this->remote_addr_rx == 0xff || fc == this->remote_addr_rx)
   }

   action is_waiting_for_data {
      _DEBUG("waiting: rx_user_data_got_len=%d", rx_user_data_got_len),
      (rx_user_data_got_len++ < rx_user_data_len)
   }

   action is_checksum_correct {
      _DEBUG("is_checksum_correct"),
      (this->rx_checksum == fc)
   }







   fmt = (any);
   len = (any);
   tgt = (any);
   src = (any);
   data = (any);
   checksum = (any);

   message = 
      (
       (fmt        when is_fmt_valid          @got_fmt       ) $got_service_byte
       (len        when is_len_valid          @got_len       ) $got_service_byte
l_tgt: (tgt        when is_tgt_valid          @got_tgt       ) $got_service_byte
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

/**
 * Reset current Rx message. It is called by ragel parser whenever we start
 * receiving next message.
 */
void Codec_ISO14230::msgReset()
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


/* protected    */

/* public       */

void Codec_ISO14230::addRawRxData(const vector<uint8_t> &data)
{
    //TODO: refactor, use iterators
    for (size_t i = 0; i < data.size(); i++){
        raw_data.push_back(data[i]);
    }
    _DEBUG("---new raw data, size=%d, new raw_data.size()=%d, cur_raw_data_idx=%d",
       data.size(),
       raw_data.size(),
       cur_raw_data_idx
    );

   const uint8_t *p = raw_data.data() + cur_raw_data_idx;
   const uint8_t *pe = raw_data.data() + raw_data.size();
   int cs = this->ragel_cs;
   const uint8_t *eof = nullptr;

   size_t del_from_beginning = 0;

   //-- execute machine
   %%{
      write exec;
   }%%

   //-- remember ragel machine's current state
   ragel_cs = cs;
   //-- and remember current position in raw data
   cur_raw_data_idx = p - raw_data.data();

   //-- if need to delete some data from the beginning, do it
   if (del_from_beginning > 0){
      _DEBUG("deleting %d bytes..", del_from_beginning);

      if (del_from_beginning > raw_data.size()){
         //-- should never happen: need to delete more data that is present
         qDebug("error: del_from_beginning=%u is more than raw_data.size()=%u",
            del_from_beginning,
            raw_data.size()
         );
      }

      //-- actually delete data from the beginning
      raw_data.erase(raw_data.begin(), raw_data.begin() + del_from_beginning);
      //-- adjust cur_raw_data_idx accordingly
      cur_raw_data_idx -= del_from_beginning;

      _DEBUG("new raw_data.size()=%d", raw_data.size());
   }
}

void Codec_ISO14230::clearRawRxData()
{
   msgReset();

   this->raw_data.clear();
   this->cur_raw_data_idx = 0;
}

DataMsg Codec_ISO14230::encodeMessage(const vector<uint8_t> &data) const
{
   DataMsg ret{};

   //-- put length
   if (data.size() >= 0x40){
      ret.addDataByte(DataPart::DataType::SERVICE, this->fmt_tx);
      ret.addDataByte(DataPart::DataType::SERVICE, data.size());
   } else {
      ret.addDataByte(DataPart::DataType::SERVICE, this->fmt_tx | data.size());
   }

   //-- push target and source addresses
   ret.addDataByte(DataPart::DataType::SERVICE, remote_addr_tx);
   ret.addDataByte(DataPart::DataType::SERVICE, own_addr_tx);

   //-- push user data
   for (auto user_byte : data){
      ret.addDataByte(DataPart::DataType::USER, user_byte);
   }

   //-- calculate and push checksum
   {
      uint8_t checksum = 0;
      std::shared_ptr<vector<uint8_t>> p_raw_data = ret.getRawData();
      for (auto byte : *p_raw_data){
         checksum += byte;
      }
      ret.addDataByte(DataPart::DataType::SERVICE, checksum);
   }

   return ret;
}

std::vector<std::shared_ptr<ReqHandler>> Codec_ISO14230::getStdHandlers() const
{
    //-- just return empty vector
    auto ret = std::vector<std::shared_ptr<ReqHandler>>{};


    {
        std::shared_ptr<ReqHandler> p_handler = std::make_shared<ReqHandler>(
                "ISO14230 Std",

                "(function(inputMsg){ \n"
                "    var handled = false;\n"
                "    var outputArr;\n"
                "    var descr;\n"
                "    var len = inputMsg.byteArr.getLength();\n"
                "    var mode = inputMsg.byteArr.getU08(0);\n"
                "\n"
                "    if (len === 1 && mode === 0x81){\n"
                //TODO: timeout 60 ms, i.e. setTimeout
                "        outputArr = factory.createByteArr();\n"

                // KB1: 0xEA: length in fmt byte is NOT supported
                //      0xEB: length in fmt byte is supported
                "        outputArr.putU08Array(0, [ (mode | 0x40), 0xea/*KB1*/, 0x8f/*KB2*/ ]);\n"
                "        descr = 'STC';\n"
                "    } else if (mode === 0x83){\n"
                "        outputArr = factory.createByteArr();\n"
                "        outputArr.putU08Array(0, [ (mode | 0x50), 0x00 ]);\n"
                "        descr = 'ACP (access communication param)';\n"
                "    } else if (mode === 0x10){\n"
                "        outputArr = factory.createByteArr();\n"
                "        outputArr.putU08Array(0, [ (mode | 0x50), 0x00 ]);\n"
                "        descr = 'STDS';\n"
                "    } else if (mode === 0x3e){\n"
                "        outputArr = factory.createByteArr();\n"
                "        outputArr.putU08(0, (mode | 0x40));\n"
                "        descr = 'TP';\n"
                "    };\n"
                "\n"
                "    if (outputArr !== undefined){\n"
                "        io.writeEncoded(outputArr, descr);\n"
                "\n"
                "        handled = true;\n"
                "    };\n"
                "\n"
                "    return {\n"
                "       handled: handled\n"
                "    };\n"
                " })\n"
                );

        ret.push_back(p_handler);
    }

    return ret;
}


void Codec_ISO14230::accept(CodecVisitor &visitor)
{
    visitor.visit(*this);
}





void Codec_ISO14230::setFmtRx(uint8_t fmt_rx)
{
    this->fmt_rx = fmt_rx;
    emit settingsChanged();
}

void Codec_ISO14230::setOwnAddrRx(uint8_t own_addr_rx)
{
    this->own_addr_rx = own_addr_rx;
    emit settingsChanged();
}

void Codec_ISO14230::setRemoteAddrRx(uint8_t remote_addr_rx)
{
    this->remote_addr_rx = remote_addr_rx;
    emit settingsChanged();
}



void Codec_ISO14230::setFmtTx(uint8_t fmt_tx)
{
    this->fmt_tx = fmt_tx;
    emit settingsChanged();
}

void Codec_ISO14230::setOwnAddrTx(uint8_t own_addr_tx)
{
    this->own_addr_tx = own_addr_tx;
    emit settingsChanged();
}

void Codec_ISO14230::setRemoteAddrTx(uint8_t remote_addr_tx)
{
    this->remote_addr_tx = remote_addr_tx;
    emit settingsChanged();
}




uint8_t Codec_ISO14230::getFmtRx() const
{
    return fmt_rx;
}

uint8_t Codec_ISO14230::getOwnAddrRx() const
{
    return own_addr_rx;
}

uint8_t Codec_ISO14230::getRemoteAddrRx() const
{
    return remote_addr_rx;
}




uint8_t Codec_ISO14230::getFmtTx() const
{
    return fmt_tx;
}

uint8_t Codec_ISO14230::getOwnAddrTx() const
{
    return own_addr_tx;
}

uint8_t Codec_ISO14230::getRemoteAddrTx() const
{
    return remote_addr_tx;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


