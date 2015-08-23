/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _TEST_HTCODEC_ISO14230_H
#define _TEST_HTCODEC_ISO14230_H


/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>
#include "bt_codec_iso14230.h"
#include "bt_codec_types.h"

#include <queue>
#include <iostream>


/*******************************************************************************
 * TESTS CLASS
 ******************************************************************************/

class TestCodecISO14230: public QObject
{
Q_OBJECT

public:
    TestCodecISO14230() :
        codec(BTCore::CodecNum::ISO_14230)
    {
        codec.setOwnAddrTx(0x01);
        codec.setRemoteAddrTx(0x02);
    connect(
            &codec, &BTCore::Codec_ISO14230::messageDecoded,
            this, &TestCodecISO14230::messageDecoded
           );
    std::cout << "constructed" << std::endl;
    }


    ~TestCodecISO14230()
    {
        std::cout << "destructed" << std::endl;
    }

private:
    BTCore::Codec_ISO14230 codec;
    std::queue<BTCore::DataMsg> rx_msgs;


private slots:
    void decode_summary();
    void encode();
    void decode_encoded();
    void decode_with_return_after_error();

public slots:
    void messageDecoded(const BTCore::DataMsg &msg);
};


#endif


