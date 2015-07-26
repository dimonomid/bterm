

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>

#include "test_htcodec_iso14230.h"
#include "test_htdatamsg.h"




/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

int main(int argc, char **argv)
{
   int status = 0;

   //-- run all tests
   {
      TestCodecISO14230 tc;
      status |= QTest::qExec(&tc, argc, argv);
   }

   {
      TestDataMsg tc;
      status |= QTest::qExec(&tc, argc, argv);
   }

   return status;
}

