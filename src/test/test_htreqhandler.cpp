/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include <QJSEngine>

#include "test_htreqhandler.h"
#include "htreqhandler.h"


using namespace HTCore;
using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

TestReqHandler::TestReqHandler() :
    p_engine(std::make_shared<QJSEngine>())
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
    QJSValue script_ctx = p_engine->evaluate("({})");
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
        result = handler.handle(input_data, script_ctx);
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
        result = handler.handle(input_data, script_ctx);
        QCOMPARE(result, ReqHandler::Result::OK_NOT_HANDLED);
        auto p_resp = handler.getResponse();

        //-- response should be empty
        vector<uint8_t> expected_resp = {};
        QCOMPARE(*p_resp, expected_resp);
    }
}


void TestReqHandler::errorsTest()
{
    ReqHandler handler("handler", p_engine, "");
    QJSValue script_ctx = p_engine->evaluate("({})");
    ReqHandler::Result result = ReqHandler::Result::UNKNOWN;

    handler.setScript(
            "(1)"
            );

    {
        vector<uint8_t> input_data = {};
        result = handler.handle(input_data, script_ctx);
        QCOMPARE(result, ReqHandler::Result::ERROR);
        QCOMPARE(handler.getLastError(), ReqHandler::Error::SCRIPT_IS_NOT_FUNCTION);
        auto p_resp = handler.getResponse();
    }

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
            " }"//NOTE: no closing bracket, causes parse error
            );

    {
        vector<uint8_t> input_data = {};
        result = handler.handle(input_data, script_ctx);
        QCOMPARE(result, ReqHandler::Result::ERROR);
        QCOMPARE(handler.getLastError(), ReqHandler::Error::EXCEPTION);
        QCOMPARE(handler.getLastExceptionDetails()["lineNumber"].toInt(), 1);
        auto p_resp = handler.getResponse();
    }

    handler.setScript(
            "(function(inputArr, outputArr){ "
            "     var handled = false;"

            "     outputArr.someFunction(1, 0x04);"//NOTE: non-existing function someFunction

            "     return {"
            "        handled: handled"
            "     };"
            " })"
            );

    {
        vector<uint8_t> input_data = {};
        result = handler.handle(input_data, script_ctx);
        QCOMPARE(result, ReqHandler::Result::ERROR);
        QCOMPARE(handler.getLastError(), ReqHandler::Error::EXCEPTION);
        auto p_resp = handler.getResponse();
    }

}

void TestReqHandler::scriptCtxTest()
{
    QJSValue script_ctx = p_engine->evaluate("({})");
    ReqHandler::Result result = ReqHandler::Result::UNKNOWN;

    vector<uint8_t> input_data = {};

    //-- sets variable testValue in "this"
    {
        ReqHandler handler("handler", p_engine, "");
        handler.setScript(
                "(function(inputArr, outputArr){ "
                "     var handled = false;"

                "     this.testValue = 0xaa;"

                "     return {"
                "        handled: handled"
                "     };"
                " })"
                );

        result = handler.handle(input_data, script_ctx);
        QCOMPARE(result, ReqHandler::Result::OK_NOT_HANDLED);
    }

    //-- sets variable testValue2 in "this"
    {
        ReqHandler handler("handler", p_engine, "");
        handler.setScript(
                "(function(inputArr, outputArr){ "
                "     var handled = false;"

                "     this.testValue2 = 0x12345678;"

                "     return {"
                "        handled: handled"
                "     };"
                " })"
                );

        result = handler.handle(input_data, script_ctx);
        QCOMPARE(result, ReqHandler::Result::OK_NOT_HANDLED);
    }

    //-- uses both variables testValue and testValue2, that were set
    //   in previous handlers
    {
        ReqHandler handler("handler", p_engine, "");
        handler.setScript(
                "(function(inputArr, outputArr){ "
                "     outputArr.putU08(0, this.testValue);"
                "     outputArr.putU32(4, this.testValue2, BIG_END);"
                "     outputArr.putU32(8, this.testValue,  LITTLE_END);"

                "     return {"
                "        handled: true"
                "     };"
                " })"
                );

        result = handler.handle(input_data, script_ctx);
        QCOMPARE(result, ReqHandler::Result::OK_HANDLED);


        auto p_resp = handler.getResponse();

        //-- check response
        vector<uint8_t> expected_resp = {
            0xaa,                   //-- by putU08(0, this.testValue);
            0x00, 0x00, 0x00,       //-- untouched
            0x12, 0x34, 0x56, 0x78, //-- by putU32(4, this.testValue2, BIG_END);
            0xaa, 0x00, 0x00, 0x00  //-- by putU32(4, this.testValue,  LITTLE_END);
        };
        QCOMPARE(*p_resp, expected_resp);
    }

}



