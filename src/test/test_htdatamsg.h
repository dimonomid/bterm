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

#include "bt_datamsg.h"

/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestDataMsg: public QObject
{
Q_OBJECT

public:
    explicit TestDataMsg();

private:
    std::vector<BTCore::DataPart> data_parts;
    BTCore::DataMsg msg;

private slots:
    void testDataParts();
    void testUserData();
    void testRawData();
    void testClear();

};


#endif


