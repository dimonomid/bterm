/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include "htcodec_iso14230.h"

#include <iostream>


/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestHTCodecISO14230: public QObject
{
Q_OBJECT

private slots:
void encode1();

public slots:
   void messageDecoded(const HTDataMsg &msg);
};



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

void TestHTCodecISO14230::messageDecoded(const HTDataMsg &msg)
{
   cout << std::string("decoded: ") << msg.toString() << std::string("\n");
}



/*******************************************************************************
 * TESTS IMPLEMENTATION
 ******************************************************************************/

void TestHTCodecISO14230::encode1()
{
   //QString str = "Hello";
   //QCOMPARE(str.toUpper(), QString("HELLO"));

   HTCodec_ISO14230 codec{};

   connect(
         &codec, SIGNAL(messageDecoded(const HTDataMsg &)),
         this, SLOT(messageDecoded(const HTDataMsg &))
         );


   vector<unsigned char> data{0x83, 0x01, 0x02};
   data.push_back(0x02);
   data.push_back(0x02);
   data.push_back(0x02);
   data.push_back(0x8c);

   codec.addRawRxData(data);
   data.clear();

   data.push_back(0x02);

   data.push_back(0x80);
   data.push_back(0x02);

   codec.addRawRxData(data);
   data.clear();

   data.push_back(0x01);
   data.push_back(0x02);
   data.push_back(0x03);
   data.push_back(0x03);
   data.push_back(0x8b);

   codec.addRawRxData(data);

   QCOMPARE(1, 2);
}



/*******************************************************************************
 * BOILERPLATE TEST CODE
 ******************************************************************************/

//-- expands to a simple main() function that runs all the test functions.
QTEST_MAIN(TestHTCodecISO14230);

//-- when both declaration and implementation of class are in a .cpp file,
//   we also need to include the generated moc file to make Qt's introspection
//   work.
#include "test_htcodec_iso14230.moc"


