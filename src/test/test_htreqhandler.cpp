/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include <QtQml>
#include <QJSEngine>

#include "test_htreqhandler.h"
#include "bt_reqhandler.h"

#include "bytearr_read.h"
#include "bytearr_read_write.h"
#include "script_factory.h"


using namespace BTCore;
using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

TestReqHandler::TestReqHandler() :
    p_engine(std::make_shared<QJSEngine>()),
    p_script_factory(std::make_shared<ScriptFactory>())
{
    qmlRegisterType<ByteArrRead>     ();
    qmlRegisterType<ByteArrReadWrite>("", 1, 0, "ByteArrReadWrite");
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/



/*******************************************************************************
 * PRIVATE METHODS
 ******************************************************************************/

QJSValue TestReqHandler::createInputMsgFromInputData(vector<uint8_t> input_data)
{
    //-- create an object that will be given to handlers as input message
    QJSValue input_msg_jsval = p_engine->newObject();

    //-- actual input byte array
    //ByteArrRead ba_in {input_data};
    ByteArrRead *p_ba_in = new ByteArrRead(input_data);
    QJSValue ba_in_jsval = p_engine->newQObject(p_ba_in);
    //QQmlEngine::setObjectOwnership(p_ba_in, QQmlEngine::CppOwnership);

    input_msg_jsval.setProperty("byteArr", ba_in_jsval);

    return input_msg_jsval;
}



/*******************************************************************************
 * TESTS IMPLEMENTATION
 ******************************************************************************/

void TestReqHandler::generalTest()
{
    ReqHandler handler("handler", p_engine, p_script_factory, "");
    QJSValue script_ctx = p_engine->evaluate("({})");
    ReqHandler::Result result = ReqHandler::Result::UNKNOWN;

    handler.setScript(
            "(function(inputMsg){ \n"
            "     var inputArr = inputMsg.byteArr;\n"
            "     var handled = false;\n"
            "     var outputArr = factory.createByteArr();\n"

            "     if (inputArr.getU08(0) === 0x03){\n"
            "        outputArr.putU08(1, 0x04);\n"
            "        handled = true;\n"
            "     };\n"

            "     return {\n"
            "        handled: handled,\n"
            "        response: outputArr\n"
            "     };\n"
            " })\n"
            );

    {
        vector<uint8_t> input_data = {
            0x03, 0x02, 0x03, 0x04, 0x05
        };

        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
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
        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
        QCOMPARE(result, ReqHandler::Result::OK_NOT_HANDLED);
        auto p_resp = handler.getResponse();

        //-- response should be empty
        vector<uint8_t> expected_resp = {};
        QCOMPARE(*p_resp, expected_resp);
    }
}

/**
 * when script returned "handled": true, but set no response, then it should
 * still be considered as OK_HANDLED.
 */
void TestReqHandler::noResponseTest()
{
    ReqHandler handler("handler", p_engine, p_script_factory, "");
    QJSValue script_ctx = p_engine->evaluate("({})");
    ReqHandler::Result result = ReqHandler::Result::UNKNOWN;

    handler.setScript(
            "(function(inputMsg){ \n"
            "     return {\n"
            "        handled: true\n"
            "     };\n"
            " })\n"
            );

    {
        vector<uint8_t> input_data = {
            0x01, 0x02, 0x03, 0x04, 0x05
        };
        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
        //-- should be handled
        QCOMPARE(result, ReqHandler::Result::OK_HANDLED);
        auto p_resp = handler.getResponse();

        //-- response should be empty
        vector<uint8_t> expected_resp = {};
        QCOMPARE(*p_resp, expected_resp);
    }
}


void TestReqHandler::errorsTest()
{
    ReqHandler handler("handler", p_engine, p_script_factory, "");
    QJSValue script_ctx = p_engine->evaluate("({})");
    ReqHandler::Result result = ReqHandler::Result::UNKNOWN;

    handler.setScript(
            "(1)"
            );

    {
        vector<uint8_t> input_data = {};
        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
        QCOMPARE(result, ReqHandler::Result::ERROR);
        QCOMPARE(handler.getLastError(), ReqHandler::Error::SCRIPT_IS_NOT_FUNCTION);
        auto p_resp = handler.getResponse();
    }

    handler.setScript(
            "(function(inputMsg){ \n"
            "     var inputArr = inputMsg.byteArr;\n"
            "     var handled = false;\n"
            "     var outputArr = factory.createByteArr();\n"

            "     if (inputArr.getU08(0) === 0x03){\n"
            "        outputArr.putU08(1, 0x04);\n"
            "        handled = true;\n"
            "     };\n"

            "     return {\n"
            "        handled: handled,\n"
            "        response: outputArr\n"
            "     };\n"
            " }\n"//NOTE: no closing bracket, causes parse error
            );

    {
        vector<uint8_t> input_data = {};
        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
        QCOMPARE(result, ReqHandler::Result::ERROR);
        QCOMPARE(handler.getLastError(), ReqHandler::Error::EXCEPTION);
        QCOMPARE(handler.getLastExceptionDetails()["lineNumber"].toInt(), 14);
        auto p_resp = handler.getResponse();
    }

    handler.setScript(
            "(function(inputMsg){ "
            "     var inputArr = inputMsg.byteArr;\n"
            "     var handled = false;"
            "     var outputArr = factory.createByteArr();\n"

            "     outputArr.someFunction(1, 0x04);"//NOTE: non-existing function someFunction

            "     return {"
            "        handled: handled,"
            "        response: outputArr"
            "     };"
            " })"
            );

    {
        vector<uint8_t> input_data = {};
        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
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
        ReqHandler handler("handler", p_engine, p_script_factory, "");
        handler.setScript(
                "(function(inputMsg){ "
                "     var inputArr = inputMsg.byteArr;\n"
                "     var handled = false;"
                "     var outputArr = factory.createByteArr();\n"

                "     this.testValue = 0xaa;"

                "     return {"
                "        handled: handled,"
                "        response: outputArr"
                "     };"
                " })"
                );

        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
        QCOMPARE(result, ReqHandler::Result::OK_NOT_HANDLED);
    }

    //-- sets variable testValue2 in "this"
    {
        ReqHandler handler("handler", p_engine, p_script_factory, "");
        handler.setScript(
                "(function(inputMsg){ "
                "     var inputArr = inputMsg.byteArr;\n"
                "     var handled = false;"
                "     var outputArr = factory.createByteArr();\n"

                "     this.testValue2 = 0x12345678;"

                "     return {"
                "        handled: handled,"
                "        response: outputArr"
                "     };"
                " })"
                );

        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
        QCOMPARE(result, ReqHandler::Result::OK_NOT_HANDLED);
    }

    //-- uses both variables testValue and testValue2, that were set
    //   in previous handlers
    {
        ReqHandler handler("handler", p_engine, p_script_factory, "");
        handler.setScript(
                "(function(inputMsg){ "
                "     var inputArr = inputMsg.byteArr;\n"
                "     var outputArr = factory.createByteArr();\n"
                "     outputArr.putU08(0, this.testValue);"
                "     outputArr.putU32(4, this.testValue2, BIG_END);"
                "     outputArr.putU32(8, this.testValue,  LITTLE_END);"

                "     return {"
                "        handled: true,"
                "        response: outputArr"
                "     };"
                " })"
                );

        result = handler.handle(createInputMsgFromInputData(input_data), script_ctx);
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



