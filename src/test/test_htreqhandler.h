/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _TEST_HTREQHANDLER_H
#define _TEST_HTREQHANDLER_H


/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include <QJSValue>

#include <memory>
#include <vector>
#include <cstdint>



namespace HTCore {
    class ScriptFactory;
}

class QJSEngine;

/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestReqHandler: public QObject
{
Q_OBJECT

public:
    explicit TestReqHandler();

private:
    std::shared_ptr<QJSEngine> p_engine;
    std::shared_ptr<HTCore::ScriptFactory> p_script_factory;

private:
    QJSValue createInputMsgFromInputData(std::vector<uint8_t> input_data);

private slots:
    void generalTest();
    void errorsTest();
    void scriptCtxTest();

};


#endif


