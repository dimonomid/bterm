/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>

//#include "test_helpers.h"
#include "test_htbytearr.h"
#include "bytearr_read_write.h"


using namespace HTCore;
using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

TestByteArr::TestByteArr()
{
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/



/*******************************************************************************
 * PRIVATE METHODS
 ******************************************************************************/

void TestByteArr::doFillTest(uint8_t fill_byte)
{
   //-- test with default fill (0x00)
   ByteArrReadWrite byte_arr {};
   if (fill_byte != 0x00){
      byte_arr.setFillByte(fill_byte);
   }

   //-- length should be 0 now
   QCOMPARE(byte_arr.getData()->size(), 0U);

   byte_arr.putU08(5, 0xa0);

   //-- length should be 6
   QCOMPARE(byte_arr.getData()->size(), 6U);

   //-- check actual data
   {
      vector<uint8_t> expected_data = {
         fill_byte, fill_byte, fill_byte, fill_byte, fill_byte, 0xa0
      };

      auto p_actual_data = byte_arr.getData();

      QCOMPARE(*p_actual_data, expected_data);
   }

   byte_arr.putU08(2, 0x05);

   //-- length should still be 6
   QCOMPARE(byte_arr.getData()->size(), 6U);

   //-- check actual data
   {
      vector<uint8_t> expected_data = {
         fill_byte, fill_byte, 0x05, fill_byte, fill_byte, 0xa0
      };

      auto p_actual_data = byte_arr.getData();

      QCOMPARE(*p_actual_data, expected_data);
   }

   byte_arr.putU08(10, 0xf0);

   //-- length should be 11
   QCOMPARE(byte_arr.getData()->size(), 11U);

   //-- check actual data
   {
      vector<uint8_t> expected_data = {
         fill_byte, fill_byte, 0x05, fill_byte, fill_byte, 0xa0, fill_byte, fill_byte, fill_byte, fill_byte, 0xf0
      };

      auto p_actual_data = byte_arr.getData();

      QCOMPARE(*p_actual_data, expected_data);
   }
}




/*******************************************************************************
 * TESTS IMPLEMENTATION
 ******************************************************************************/

void TestByteArr::fillAndResizeTest()
{
   doFillTest(0x00);
   doFillTest(0x11);
}

void TestByteArr::putGetTest()
{
   ByteArrReadWrite byte_arr {};

   //-- length should be 0 now
   QCOMPARE(byte_arr.getData()->size(), 0U);

   byte_arr.putU08(5, 0xa0);

   QCOMPARE(byte_arr.getU08(4), (double)0x00);
   QCOMPARE(byte_arr.getU08(5), (double)0xa0);
   QCOMPARE(byte_arr.getU08(6), (double)0xff); //-- out of range: should be 0xff

   QCOMPARE(byte_arr.getU16(6), (double)0xffff);
   QCOMPARE(byte_arr.getU16(5), (double)0xffff);
   QCOMPARE(byte_arr.getU16(4), (double)0xa000);
   QCOMPARE(byte_arr.getU16(4, ByteArrRead::BIG_END), (double)0x00a0);

   QCOMPARE(byte_arr.getU32(6), (double)0xffffffff);
   QCOMPARE(byte_arr.getU32(5), (double)0xffffffff);
   QCOMPARE(byte_arr.getU32(4), (double)0xffffffff);
   QCOMPARE(byte_arr.getU32(3), (double)0xffffffff);
   QCOMPARE(byte_arr.getU32(2), (double)0xa0000000);
   QCOMPARE(byte_arr.getU32(2, ByteArrRead::BIG_END), (double)0xa0);

   byte_arr.putU16(6, 0x1234);
   {
      vector<uint8_t> expected_data = {
         0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x34, 0x12
      };
      auto p_actual_data = byte_arr.getData();
      QCOMPARE(*p_actual_data, expected_data);
   }

   byte_arr.putU16(6, 0x1234, ByteArrReadWrite::BIG_END);
   {
      vector<uint8_t> expected_data = {
         0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x12, 0x34
      };
      auto p_actual_data = byte_arr.getData();
      QCOMPARE(*p_actual_data, expected_data);
   }

   byte_arr.putU32(6, 0x12345678);
   {
      vector<uint8_t> expected_data = {
         0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x78, 0x56, 0x34, 0x12
      };
      auto p_actual_data = byte_arr.getData();
      QCOMPARE(*p_actual_data, expected_data);
   }

   byte_arr.putU32(6, 0x12345678, ByteArrReadWrite::BIG_END);
   {
      vector<uint8_t> expected_data = {
         0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x12, 0x34, 0x56, 0x78
      };
      auto p_actual_data = byte_arr.getData();
      QCOMPARE(*p_actual_data, expected_data);
   }

   byte_arr.putU08(0, 0x12);
   QCOMPARE(byte_arr.getU08(0), (double)0x12);

   byte_arr.putU16(0, 0x1234);
   QCOMPARE(byte_arr.getU16(0), (double)0x1234);

   byte_arr.putU32(0, 0x12345678);
   QCOMPARE(byte_arr.getU32(0), (double)0x12345678);

   byte_arr.putS08(0, 2);
   QCOMPARE(byte_arr.getU08(0), (double)2);
   byte_arr.putS08(0, -2);
   QCOMPARE(byte_arr.getS08(0), (double)-2);

   byte_arr.putS16(0, 2);
   QCOMPARE(byte_arr.getU16(0), (double)2);
   byte_arr.putS16(0, -2);
   QCOMPARE(byte_arr.getS16(0), (double)-2);

   byte_arr.putS32(0, 2);
   QCOMPARE(byte_arr.getU32(0), (double)2);
   byte_arr.putS32(0, -2);
   QCOMPARE(byte_arr.getS32(0), (double)-2);

}


