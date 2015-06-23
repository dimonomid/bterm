/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>

#include "test_helpers.h"
#include "test_htdatamsg.h"
#include "htdatamsg.h"

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

TestHTDataMsg::TestHTDataMsg()
{
   {
      HTDataPart part{HTDataPart::DataType::SERVICE, {0x01, 0x02, 0x03}};
      data_parts.push_back(part);
   }

   {
      HTDataPart part{HTDataPart::DataType::USER, {0x04, 0x05, 0x06, 0x07, 0x08}};
      data_parts.push_back(part);
   }

   {
      HTDataPart part{HTDataPart::DataType::SERVICE, {0x09}};
      data_parts.push_back(part);
   }

   {
      HTDataPart part{HTDataPart::DataType::USER, {0x0a, 0x0b, 0x0c}};
      data_parts.push_back(part);
   }

   {
      HTDataPart part{HTDataPart::DataType::SERVICE, {0x0d}};
      data_parts.push_back(part);
   }

   for (size_t i = 0; i < data_parts.size(); i++){
      auto part = data_parts[i];

      switch (i){
         case 0:
            //-- first part: feed SERVICE data byte-by-byte
            for (uint8_t byte : part.getData(HTDataPart::DataType::SERVICE)){
               msg.addData(HTDataPart::DataType::SERVICE, byte);
            }
            break;
         case 1:
            //-- second part: feed USER data as vector
            msg.addData(HTDataPart::DataType::USER, part.getData(HTDataPart::DataType::USER));
            break;
         default:
            //-- any other part: feed data as data_part
            msg.addData(part);
            break;
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

   QCOMPARE(msg.getUserData(), user_data);
}

void TestHTDataMsg::testRawData()
{
   std::vector<uint8_t> user_data {
      0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d
   };

   QCOMPARE(msg.getRawData(), user_data);
}

void TestHTDataMsg::testDataParts()
{
#if 0
   QCOMPARE(msg.getDataParts(), data_parts);

   //-- try to change type and make sure data parts aren't considered as equal anymore
   data_parts[0].type = HTDataPart::Type::USER;
   QVERIFY(data_parts != msg.getDataParts());

   //-- revert back
   data_parts[0].type = HTDataPart::Type::SERVICE;
   QVERIFY(data_parts == msg.getDataParts());

   //-- push some extra data
   data_parts[0].data.push_back(0x01);
   QVERIFY(data_parts != msg.getDataParts());
#endif

}



