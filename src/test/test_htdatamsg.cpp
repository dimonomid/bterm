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
   {
      HTDataPart part{HTDataPart::Type::SERVICE, {0x01, 0x02, 0x03}};
      data_parts.push_back(part);
   }

   {
      HTDataPart part{HTDataPart::Type::USER, {0x04, 0x05, 0x06, 0x07, 0x08}};
      data_parts.push_back(part);
   }

   {
      HTDataPart part{HTDataPart::Type::SERVICE, {0x09}};
      data_parts.push_back(part);
   }

   {
      HTDataPart part{HTDataPart::Type::USER, {0x0a, 0x0b, 0x0c}};
      data_parts.push_back(part);
   }

   {
      HTDataPart part{HTDataPart::Type::SERVICE, {0x0d}};
      data_parts.push_back(part);
   }


   //-- first part of data will be fed byte-by-byte, others will be
   //   fed as vector at once
   //   (just to make sure that both feed methods work)
   bool firstPartFed = false;

   for (auto part : data_parts){

      if (!firstPartFed){
         //-- feed data byte-by-byte
         for (uint8_t byte : part.data){
            msg.addData(part.type, byte);
         }

         firstPartFed = true;
      } else {
         //-- feed the whole vector of bytes
         msg.addData(part.type, part.data);
      }
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



