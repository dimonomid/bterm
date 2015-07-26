

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include <QApplication>

#include "test_htcodec_iso14230.h"
#include "test_htdatamsg.h"
#include "test_htbytearr.h"
#include "test_htreqhandler.h"




/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

int main(int argc, char **argv)
{
   QApplication qappl{argc, argv};

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

   {
      TestByteArr tc;
      status |= QTest::qExec(&tc, argc, argv);
   }

   {
      TestReqHandler tc;
      status |= QTest::qExec(&tc, argc, argv);
   }

   return status;
}

