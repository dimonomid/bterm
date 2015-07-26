/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _TEST_HTBYTEARR_H
#define _TEST_HTBYTEARR_H


/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>

#include <vector>



/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestByteArr: public QObject
{
Q_OBJECT

public:
   explicit TestByteArr();

private:
   void doFillTest(uint8_t fill_byte);

private slots:
   void fillAndResizeTest();
   void putGetTest();

};


#endif


