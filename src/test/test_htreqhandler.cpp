/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include <QScriptEngine>

#include "test_htreqhandler.h"
#include "htreqhandler.h"


using namespace HTCore;
using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

TestReqHandler::TestReqHandler() :
   p_engine(std::make_shared<QScriptEngine>())
{
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/



/*******************************************************************************
 * PRIVATE METHODS
 ******************************************************************************/




/*******************************************************************************
 * TESTS IMPLEMENTATION
 ******************************************************************************/

void TestReqHandler::generalTest()
{
   ReqHandler handler("handler", p_engine, "");
   QScriptValue chain_data = p_engine->evaluate("({})");
   ReqHandler::Result result = ReqHandler::Result::UNKNOWN;

   handler.setScript(
         "(function(inputArr, outputArr){ "
         "     var handled = false;"

         "     if (inputArr.getU08(0) === 0x03){"
         "        outputArr.putU08(1, 0x04);"
         "        handled = true;"
         "     };"

         "     return {"
         "        handled: handled"
         "     };"
         " })"
         );

   {
      vector<uint8_t> input_data = {
         0x03, 0x02, 0x03, 0x04, 0x05
      };
      result = handler.handle(input_data, chain_data);
      QCOMPARE(result, ReqHandler::Result::OK_HANDLED);
      auto p_resp = handler.getResponse();

      //-- check generated response
      vector<uint8_t> expected_resp = {
         0x00, 0x04
      };
      QCOMPARE(*p_resp, expected_resp);
   }

   {
      vector<uint8_t> input_data = {
         0x01, 0x02, 0x03, 0x04, 0x05
      };
      result = handler.handle(input_data, chain_data);
      QCOMPARE(result, ReqHandler::Result::OK_NOT_HANDLED);
      auto p_resp = handler.getResponse();

      //-- response should be empty
      vector<uint8_t> expected_resp = {};
      QCOMPARE(*p_resp, expected_resp);
   }

}



