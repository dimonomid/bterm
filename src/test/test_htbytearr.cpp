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


