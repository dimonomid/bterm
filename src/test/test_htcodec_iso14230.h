/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _TEST_HTCODEC_ISO14230_H
#define _TEST_HTCODEC_ISO14230_H


/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include "htcodec_iso14230.h"

#include <queue>
#include <iostream>


/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestHTCodecISO14230: public QObject
{
Q_OBJECT

public:
   TestHTCodecISO14230() :
      codec(0x01, 0x02)
   {
   connect(
         &codec, SIGNAL(messageDecoded(const HTDataMsg &)),
         this, SLOT(messageDecoded(const HTDataMsg &))
         );
   std::cout << "constructed" << std::endl;
   }


   ~TestHTCodecISO14230()
   {
      std::cout << "destructed" << std::endl;
   }

private:
   HTCodec_ISO14230 codec;
   std::queue<HTDataMsg> rx_msgs;


private slots:
   void decode_summary();
   void encode();
   void decode_encoded();

public slots:
   void messageDecoded(const HTDataMsg &msg);
};


#endif


