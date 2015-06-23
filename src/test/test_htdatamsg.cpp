/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include "test_htdatamsg.h"
#include "htdatamsg.h"


/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

TestHTDataMsg::TestHTDataMsg()
{
   std::vector<uint8_t> part;

   //-- service data
   part.push_back(0x01);
   part.push_back(0x02);
   part.push_back(0x03);

   data.push_back(part);
   part.clear();

   //-- user data
   part.push_back(0x04);
   part.push_back(0x05);
   part.push_back(0x06);
   part.push_back(0x07);
   part.push_back(0x08);

   data.push_back(part);
   part.clear();

   //-- service data
   part.push_back(0x09);

   data.push_back(part);
   part.clear();

   //-- user data
   part.push_back(0x0a);
   part.push_back(0x0b);
   part.push_back(0x0c);

   data.push_back(part);
   part.clear();

   //-- service data
   part.push_back(0x0d);

   data.push_back(part);
   part.clear();



   HTDataPart::Type cur_type = HTDataPart::Type::SERVICE;
   //-- first part of data will be fed byte-by-byte, others will be
   //   fed as vector at once
   //   (just to make sure that both feed methods work)
   bool firstPartFed = false;

   for (auto part : data){

      if (!firstPartFed){
         //-- feed data byte-by-byte
         for (uint8_t byte : part){
            msg.addData(cur_type, byte);
         }

         firstPartFed = true;
      } else {
         //-- feed the whole vector of bytes
         msg.addData(cur_type, part);
      }

      //-- switch type (SERVICE / USER)
      cur_type = (cur_type == HTDataPart::Type::SERVICE 
            ? HTDataPart::Type::USER
            : HTDataPart::Type::SERVICE);
   }

}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/


/*******************************************************************************
 * TESTS IMPLEMENTATION
 ******************************************************************************/

void TestHTDataMsg::testUserData()
{
   std::vector<uint8_t> user_data {
      0x04, 0x05, 0x06, 0x07, 0x08, /* service byte 0x09 skipped */ 0x0a, 0x0b, 0x0c
   };

   QCOMPARE(user_data, msg.getUserData());
}

void TestHTDataMsg::testRawData()
{
   std::vector<uint8_t> user_data {
      0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d
   };

   QCOMPARE(user_data, msg.getRawData());
}



