/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _TEST_HTDATAMSG_H
#define _TEST_HTDATAMSG_H


/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>

#include <vector>

#include "htdatamsg.h"

/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestDataMsg: public QObject
{
Q_OBJECT

public:
   explicit TestDataMsg();

private:
   vector<DataPart> data_parts;
   DataMsg msg;

private slots:
   void testDataParts();
   void testUserData();
   void testRawData();
   void testClear();

};


#endif


