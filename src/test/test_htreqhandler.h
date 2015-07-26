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

#include <memory>


class QScriptEngine;

/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestReqHandler: public QObject
{
Q_OBJECT

public:
   explicit TestReqHandler();

private:
   std::shared_ptr<QScriptEngine> p_engine;

private slots:
   void generalTest();

};


#endif


