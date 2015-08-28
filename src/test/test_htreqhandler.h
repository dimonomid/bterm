/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _TEST_HTREQHANDLER_H
#define _TEST_HTREQHANDLER_H


#if 0

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include <QJSValue>

#include <memory>
#include <vector>
#include <cstdint>



namespace BTCore {
    class ScriptFactory;
    class JSHost;
}


/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestReqHandler: public QObject
{
Q_OBJECT

public:
    explicit TestReqHandler();

private:
    std::shared_ptr<BTCore::JSHost> p_jshost;
    std::shared_ptr<BTCore::ScriptFactory> p_script_factory;

private:
    QJSValue createInputMsgFromInputData(std::vector<uint8_t> input_data);

private slots:
    void generalTest();
    void noResponseTest();
    void errorsTest();
    void scriptCtxTest();

};

#endif

#endif


