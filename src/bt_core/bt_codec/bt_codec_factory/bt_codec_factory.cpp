/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec_factory.h"
#include "bt_codec.h"
#include "bt_codec_iso14230.h"



using namespace BTCore;

/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const CodecFactory::CodecDesc CodecFactory::CODEC_DESC[] = {

    [static_cast<int>(CodecNum::ISO_14230)] =
    {
        .key = "iso14230",
        .title = "ISO 14230"
    },

    //[static_cast<int>(CodecFactory::CodecNum::ISO_14230)]
    //= { "iso", "sddf" },
};


/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/



/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */

size_t CodecFactory::getCodecsCnt() const
{
    return static_cast<size_t>( CodecNum::_COUNT );
}


QString CodecFactory::getCodecTitle(CodecNum codec_num) const
{
    return CODEC_DESC[ static_cast<int>(codec_num) ].title;
}

QString CodecFactory::getCodecKey(CodecNum codec_num) const
{
    return CODEC_DESC[ static_cast<int>(codec_num) ].key;
}

CodecNum CodecFactory::getCodecNumByKey(QString codec_key) const
{
    CodecNum codec_num = CodecNum::_COUNT;

    for (
            size_t codec_num_int = 0;
            codec_num_int < static_cast<size_t>(CodecNum::_COUNT);
            ++codec_num_int
        )
    {
        if (CODEC_DESC[ codec_num_int ].key == codec_key){
            codec_num = static_cast<CodecNum>(codec_num_int);
            break;
        }
    }

    return codec_num;
}

std::shared_ptr<Codec> CodecFactory::createCodec(CodecNum codec_num) const
{
    std::shared_ptr<Codec> p_ret {};

    switch (codec_num){
        case CodecNum::ISO_14230:
            p_ret = std::make_shared<Codec_ISO14230>(codec_num);
            break;
        case CodecNum::_COUNT:
            break;
    }

    if (p_ret == nullptr){
        qDebug("error: no codec was created for number=%d",
                static_cast<int>(codec_num)
                );
    }

    return p_ret;
}

std::shared_ptr<Codec> CodecFactory::createCodecByKey(QString codec_key) const
{
    return createCodec( getCodecNumByKey(codec_key) );
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


