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

class TestHTDataMsg: public QObject
{
Q_OBJECT

public:
   explicit TestHTDataMsg();

private:
   vector<HTDataPart> data_parts;
   HTDataMsg msg;

private slots:
   void testUserData();
   void testRawData();
   void testDataParts();

};


#endif


