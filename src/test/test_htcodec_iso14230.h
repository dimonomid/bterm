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

class TestCodecISO14230: public QObject
{
Q_OBJECT

public:
   TestCodecISO14230() :
      codec(0x01, 0x02)
   {
   connect(
         &codec, &HTCore::Codec_ISO14230::messageDecoded,
         this, &TestCodecISO14230::messageDecoded
         );
   std::cout << "constructed" << std::endl;
   }


   ~TestCodecISO14230()
   {
      std::cout << "destructed" << std::endl;
   }

private:
   HTCore::Codec_ISO14230 codec;
   std::queue<HTCore::DataMsg> rx_msgs;


private slots:
   void decode_summary();
   void encode();
   void decode_encoded();

public slots:
   void messageDecoded(const HTCore::DataMsg &msg);
};


#endif


