/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include "test_htcodec_iso14230.h"

#include "bt_codec_iso14230.h"

#include <iostream>
#include <queue>
#include <random>


using namespace BTCore;
using namespace std;

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

void TestCodecISO14230::messageDecoded(const DataMsg &msg)
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
void TestCodecISO14230::decode_summary()
{
    codec.setOwnAddrRx(0xff);
    codec.setRemoteAddrRx(0xff);
    codec.clearRawRxData();

    vector<uint8_t> data{0x83, 0x01, 0x02};
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
        vector<uint8_t> expected_user_data{2, 2, 2};

        //-- compare message contents
        std::shared_ptr<vector<uint8_t>> p_user_data = rx_msgs.front().getUserData();
        QCOMPARE(*p_user_data, expected_user_data);
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
        vector<uint8_t> expected_user_data{3, 4};

        std::shared_ptr<vector<uint8_t>> p_user_data = rx_msgs.front().getUserData();
        QCOMPARE(*p_user_data, expected_user_data);
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

    //-- check message with different fmt mask and rx/tx addr specified
    {
        codec.clearRawRxData();

        codec.setFmtRx(0xc0);
        codec.setOwnAddrRx(0x40);
        codec.setRemoteAddrRx(0x41);

        codec.setFmtTx(0x80);
        codec.setOwnAddrTx(0x03);
        codec.setRemoteAddrTx(0x04);

        vector<uint8_t> data{
            //-- correct message
            0xc3, 0x40, 0x41, 0x02, 0x02, 0x02, 0x4a,
        };

        codec.addRawRxData(data);

        //-- next messages should be already received
        QCOMPARE(rx_msgs.size(), (unsigned int)1);

        //-- check message contents
        {
            vector<uint8_t> expected_user_data{2, 2, 2};

            //-- compare message contents
            std::shared_ptr<vector<uint8_t>> p_user_data = rx_msgs.front().getUserData();
            QCOMPARE(*p_user_data, expected_user_data);
            rx_msgs.pop();
        }
    }

    //-- check message with separate len
    {
        codec.clearRawRxData();

        codec.setFmtRx(0xc0);
        codec.setOwnAddrRx(0x40);
        codec.setRemoteAddrRx(0x41);

        codec.setFmtTx(0x80);
        codec.setOwnAddrTx(0x03);
        codec.setRemoteAddrTx(0x04);

        vector<uint8_t> data{
            //-- correct message
            0xc0, 0x40, 0x41, 0x03, 0x02, 0x02, 0x02, 0x4a,
        };

        codec.addRawRxData(data);

        //-- next messages should be already received
        QCOMPARE(rx_msgs.size(), (unsigned int)1);

        //-- check message contents
        {
            vector<uint8_t> expected_user_data{2, 2, 2};

            //-- compare message contents
            std::shared_ptr<vector<uint8_t>> p_user_data = rx_msgs.front().getUserData();
            QCOMPARE(*p_user_data, expected_user_data);
            rx_msgs.pop();
        }
    }

    //-- check message with wrong remote addr
    {
        codec.clearRawRxData();

        codec.setFmtRx(0xc0);
        codec.setOwnAddrRx(0x40);
        codec.setRemoteAddrRx(0x42);//wrong: need 0x41

        codec.setFmtTx(0x80);
        codec.setOwnAddrTx(0x03);
        codec.setRemoteAddrTx(0x04);

        vector<uint8_t> data{
            //-- correct message
            0xc3, 0x40, 0x41, 0x02, 0x02, 0x02, 0x4a,
        };

        codec.addRawRxData(data);

        //-- no messages should be received
        QCOMPARE(rx_msgs.size(), (unsigned int)0);
    }

    //-- check message with wrong local addr
    {
        codec.clearRawRxData();

        codec.setFmtRx(0xc0);
        codec.setOwnAddrRx(0x39);//wrong: need 0x40
        codec.setRemoteAddrRx(0x41);

        codec.setFmtTx(0x80);
        codec.setOwnAddrTx(0x03);
        codec.setRemoteAddrTx(0x04);

        vector<uint8_t> data{
            //-- correct message
            0xc3, 0x40, 0x41, 0x02, 0x02, 0x02, 0x4a,
        };

        codec.addRawRxData(data);

        //-- no messages should be received
        QCOMPARE(rx_msgs.size(), (unsigned int)0);
    }


}

/**
 * Try to feed some data, including garbage, and verify that everything as expected
 */
void TestCodecISO14230::decode_with_return_after_error()
{
    codec.setOwnAddrRx(0xff);
    codec.setRemoteAddrRx(0xff);
    codec.clearRawRxData();

    vector<uint8_t> data{
        //-- some garbage
        0x88, 0x01, 0x02,
            //-- correct message
            0x83, 0x01, 0x02, 0x02, 0x02, 0x02, 0x8c,
            //-- some garbage
            0x00, 0x00, 0x00, 0x00, 0x00
    };

    codec.addRawRxData(data);

    //-- number of received messages should be 1
    QCOMPARE(rx_msgs.size(), (unsigned int)1);

    {
        vector<uint8_t> expected_user_data{2, 2, 2};

        //-- compare message contents
        std::shared_ptr<vector<uint8_t>> p_user_data = rx_msgs.front().getUserData();
        QCOMPARE(*p_user_data, expected_user_data);
        rx_msgs.pop();
    }
}

void TestCodecISO14230::encode()
{
    codec.setFmtRx(0x80);
    codec.setOwnAddrRx(0x01);
    codec.setRemoteAddrRx(0x02);

    {
        codec.setFmtTx(0xc0);
        codec.setOwnAddrTx(0x03);
        codec.setRemoteAddrTx(0x04);

        vector<uint8_t> user_data{0x01, 0x02, 0x03};
        vector<uint8_t> encoded_expected{0xc3, 0x04, 0x03, 0x01, 0x02, 0x03, 0xd0};

        std::shared_ptr<vector<uint8_t>> p_encoded_data = codec.encodeMessage(user_data).getRawData();

        QCOMPARE(*p_encoded_data, encoded_expected);
    }

    {
        codec.setFmtTx(0x80);
        codec.setOwnAddrTx(0x03);
        codec.setRemoteAddrTx(0x04);

        vector<uint8_t> user_data{0x01, 0x02, 0x03};
        vector<uint8_t> encoded_expected{0x83, 0x04, 0x03, 0x01, 0x02, 0x03, 0x90};

        std::shared_ptr<vector<uint8_t>> p_encoded_data = codec.encodeMessage(user_data).getRawData();

        QCOMPARE(*p_encoded_data, encoded_expected);
    }
}

/**
 * Encode random data and decode it for all possible message lengths: [1 .. 255].
 * We should get the same user data as we encoded.
 */
void TestCodecISO14230::decode_encoded()
{
    codec.setOwnAddrRx(0xff);
    codec.setRemoteAddrRx(0xff);
    codec.clearRawRxData();

    std::default_random_engine dre;
    std::uniform_int_distribution<uint8_t> di{0, 0xff};

    //-- we will use in-instance `codec` as rx codec,
    //   let's set own and remote addresses
    codec.setOwnAddrRx(0x10);
    codec.setRemoteAddrRx(0xf1);

    //-- create another instance of ico14230 codec for tx, with
    //   reversed own and remote addresses, we will use it
    //   for encoding messages
    Codec_ISO14230 tx_codec{BTCore::CodecIdx::ISO_14230};
    tx_codec.setOwnAddrTx(0xf1);
    tx_codec.setRemoteAddrTx(0x10);

    //-- will be filled at each loop iteration
    vector<uint8_t> user_data{};

    //-- encode and decode messages of all possible sizes (1 .. 255 bytes)
    for (int user_data_len = 1; user_data_len < 0xff; user_data_len++){
        //-- there should be no decoded messages at the moment
        QCOMPARE(rx_msgs.size(), (unsigned int)0);

        //-- clear the message and fill it with random data
        user_data.clear();
        for (int i = 0; i < user_data_len; i++){
            user_data.push_back(di(dre));
        }

        //-- encode message and feed encoded data as raw data to our rx codec
        std::shared_ptr<vector<uint8_t>> p_encoded_data = tx_codec.encodeMessage(user_data).getRawData();
        codec.addRawRxData(*p_encoded_data);

        //-- messages should be already received
        QCOMPARE(rx_msgs.size(), (unsigned int)1);

        //-- compare data
        QCOMPARE(*rx_msgs.front().getUserData(), user_data);
        rx_msgs.pop();
    }
}




