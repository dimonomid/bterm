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
#include <random>


/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestHTCodecISO14230: public QObject
{
Q_OBJECT

public:
   TestHTCodecISO14230() :
      codec(0x01, 0x02)
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
   HTCodec_ISO14230 codec;
   std::queue<HTDataMsg> rx_msgs;


private slots:
   void decode_summary();
   void encode();
   void decode_encoded();

public slots:
   void messageDecoded(const HTDataMsg &msg);
};



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

void TestHTCodecISO14230::messageDecoded(const HTDataMsg &msg)
{
   //cout << std::string("decoded: ") << msg.toString() << std::string("\n");
   rx_msgs.push(msg);
}



/*******************************************************************************
 * TESTS IMPLEMENTATION
 ******************************************************************************/

/**
 * Try to feed some data, including garbage, and verify that everything as expected
 */
void TestHTCodecISO14230::decode_summary()
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

   //-- message should be already received
   QCOMPARE(rx_msgs.size(), (unsigned int)1);

   {
      vector<unsigned char> expected_user_data{2, 2, 2};

      //-- compare message contents
      QCOMPARE(rx_msgs.front().getUserData(), expected_user_data);
      rx_msgs.pop();
   }

   //-- add extra byte (garbage)
   data.push_back(0x02);

   //-- new message starts
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

void TestHTCodecISO14230::encode()
{
   vector<unsigned char> user_data{0x01, 0x02, 0x03};
   vector<unsigned char> encoded_expected{0x83, 0x02, 0x01, 0x01, 0x02, 0x03, 0x8c};

   vector<unsigned char> encoded_data = codec.encodeMessage(user_data);

   QCOMPARE(encoded_data, encoded_expected);
}

/**
 * Encode random data and decode it for all possible message lengths: [1 .. 255].
 * We should get the same user data as we encoded.
 */
void TestHTCodecISO14230::decode_encoded()
{
   std::default_random_engine dre;
   std::uniform_int_distribution<unsigned char> di{0, 0xff};

   HTCodec_ISO14230 tx_codec{0xf1, 0x10};
   codec.setOwnAddr(0x10);
   codec.setRemoteAddr(0xf1);

   vector<unsigned char> user_data{};

   //-- encode and decode messages of all possible sizes (1 .. 255 bytes)
   for (int user_data_len = 1; user_data_len < 0xff; user_data_len++){
      //-- there should be no decoded messages at the moment
      QCOMPARE(rx_msgs.size(), (unsigned int)0);

      user_data.clear();

      for (int i = 0; i < user_data_len; i++){
         user_data.push_back(di(dre));
      }

      vector<unsigned char> encoded_data = tx_codec.encodeMessage(user_data);
      codec.addRawRxData(encoded_data);

      //-- messages should be already received
      QCOMPARE(rx_msgs.size(), (unsigned int)1);

      //-- compare data
      QCOMPARE(rx_msgs.front().getUserData(), user_data);
      rx_msgs.pop();
   }
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


