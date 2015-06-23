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
   //-- feed data byte-by-byte
   {
      std::vector<uint8_t> data {0x01, 0x02, 0x03};

      for (auto byte : data){
         msg.addData(HTDataPart::DataType::SERVICE, byte);
      }
   }

   //-- feed USER data mixed: byte-by-byte and the vector at once
   {
      msg.addData(HTDataPart::DataType::USER, 0x04);

      std::vector<uint8_t> data {0x05, 0x06, 0x07};
      msg.addData(HTDataPart::DataType::USER, data);

      msg.addData(HTDataPart::DataType::USER, 0x08);
   }

   {
      HTDataPart part{HTDataPart::DataType::SERVICE, {0x09}};
      msg.addData(part);
   }

   {
      HTDataPart part{HTDataPart::DataType::USER, {0x0a, 0x0b, 0x0c}};
      msg.addData(part);
   }

   {
      HTDataPart part{};
      part.addData(HTDataPart::DataType::SERVICE, {0xfe, 0xff});
      part.addData(HTDataPart::DataType::USER, 0x3f);
      msg.addData(part);
   }

   //-- add empty part
   {
      HTDataPart part{};
      msg.addData(part);
   }

   {
      std::vector<uint8_t> data {0x0a, 0x0b, 0x0c};

      for (auto byte : data){
         msg.addData(HTDataPart::DataType::USER, byte);
      }
   }

   {
      HTDataPart part{HTDataPart::DataType::SERVICE, {0x0d}};
      msg.addData(part);
   }

   this->data_parts = msg.getDataParts();
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/


/*******************************************************************************
 * TESTS IMPLEMENTATION
 ******************************************************************************/

/**
 * Check that there is correct number of data parts
 * (addData() methods called earlier are responsible for that)
 */
void TestHTDataMsg::testDataParts()
{
   QCOMPARE(msg.getDataParts().size(), (size_t)7);
}

/**
 * Check that getUserData() does its job
 */
void TestHTDataMsg::testUserData()
{
   std::vector<uint8_t> user_data {
      0x04, 0x05, 0x06, 0x07, 0x08, 
         /* service byte 0x09 skipped */
         0x0a, 0x0b, 0x0c,
         0x3f,
         0x0a, 0x0b, 0x0c,
   };

   QCOMPARE(msg.getUserData(), user_data);
}

/**
 * Check that getRawData() does its job
 */
void TestHTDataMsg::testRawData()
{
   std::vector<uint8_t> user_data {
      0x01, 0x02, 0x03,
         0x04, 0x05, 0x06, 0x07, 0x08,
         0x09,
         0x0a, 0x0b, 0x0c,
         0xfe, 0xff,
         0x0a, 0x0b, 0x0c,
         0x0d
   };

   QCOMPARE(msg.getRawData(), user_data);
}

/**
 * Check that clear() does its job
 */
void TestHTDataMsg::testClear()
{
   msg.clear();

   QCOMPARE(msg.getUserData().size(), (size_t)0);
   QCOMPARE(msg.getRawData().size(), (size_t)0);
   QCOMPARE(msg.getDataParts().size(), (size_t)0);
}

#if 0
void TestHTDataMsg::testDataParts()
{
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

}
#endif


