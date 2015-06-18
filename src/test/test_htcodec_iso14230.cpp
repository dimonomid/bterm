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
#include <queue>


/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestHTCodecISO14230: public QObject
{
Q_OBJECT

public:
   TestHTCodecISO14230() :
      codec()
   {
   connect(
         &codec, SIGNAL(messageDecoded(const HTDataMsg &)),
         this, SLOT(messageDecoded(const HTDataMsg &))
         );
   cout << "constructed" << endl;
   }


   ~TestHTCodecISO14230()
   {
      disconnect(
            &codec, SIGNAL(messageDecoded(const HTDataMsg &)),
            this, SLOT(messageDecoded(const HTDataMsg &))
            );

      cout << "destructed" << endl;
   }

private:
   HTCodec_ISO14230 codec{};
   std::queue<HTDataMsg> rx_msgs{};


private slots:
   void encode1();
   void encode2();

public slots:
   void messageDecoded(const HTDataMsg &msg);
};



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

void TestHTCodecISO14230::messageDecoded(const HTDataMsg &msg)
{
   cout << std::string("decoded: ") << msg.toString() << std::string("\n");
   rx_msgs.push(msg);
}



/*******************************************************************************
 * TESTS IMPLEMENTATION
 ******************************************************************************/

void TestHTCodecISO14230::encode1()
{
   vector<unsigned char> data{0x83, 0x01, 0x02};
   data.push_back(0x02);
   data.push_back(0x02);
   data.push_back(0x02);

   codec.addRawRxData(data);
   data.clear();

   //-- number of received messages should be still 0
   QCOMPARE(rx_msgs.size(), (unsigned int)0);

   data.push_back(0x8c);

   codec.addRawRxData(data);
   data.clear();

   //-- messages should be already received
   QCOMPARE(rx_msgs.size(), (unsigned int)1);

   {
      vector<unsigned char> expected_user_data{2, 2, 2};

      //-- compare message contents
      QCOMPARE(rx_msgs.front().getUserData(), expected_user_data);
      rx_msgs.pop();
   }

   data.push_back(0x02);

   data.push_back(0x80);
   data.push_back(0x02);

   codec.addRawRxData(data);
   data.clear();

   data.push_back(0x01);
   data.push_back(0x02);
   data.push_back(0x03);
   data.push_back(0x04);
   data.push_back(0x8c);

   codec.addRawRxData(data);
   data.clear();

   //-- next messages should be already received
   QCOMPARE(rx_msgs.size(), (unsigned int)1);

   {
      vector<unsigned char> expected_user_data{3, 4};

      QCOMPARE(rx_msgs.front().getUserData(), expected_user_data);
      rx_msgs.pop();
   }

   //-- check message with wrong checksum
   {
      data.push_back(0x80);
      data.push_back(0x02);

      codec.addRawRxData(data);
      data.clear();

      data.push_back(0x01);
      data.push_back(0x02);
      data.push_back(0x03);
      data.push_back(0x04);
      data.push_back(0x8d);

      codec.addRawRxData(data);
      data.clear();

      //-- no messages should be received
      QCOMPARE(rx_msgs.size(), (unsigned int)0);
   }

}

void TestHTCodecISO14230::encode2()
{
   cout << "test" << endl;
}



/*******************************************************************************
 * BOILERPLATE TEST CODE
 ******************************************************************************/

int main(int argc, char **argv)
{
   int status = 0;

   {
      TestHTCodecISO14230 tc;
      status |= QTest::qExec(&tc, argc, argv);
   }

   return status;
}

//-- when both declaration and implementation of class are in a .cpp file,
//   we also need to include the generated moc file to make Qt's introspection
//   work.
#include "test_htcodec_iso14230.moc"


