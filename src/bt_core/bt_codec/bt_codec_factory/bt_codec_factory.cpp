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
#include "bt_codec_transparent.h"



using namespace BTCore;

/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const CodecFactory::CodecDesc CodecFactory::CODEC_DESC[] = {

    [static_cast<int>(CodecIdx::TRANSPARENT)] =
    {
        .key = "transparent",
        .title = "Transparent (no codec)"
    },

    [static_cast<int>(CodecIdx::ISO_14230)] =
    {
        .key = "iso14230",
        .title = "ISO 14230"
    },

    //[static_cast<int>(CodecFactory::CodecIdx::ISO_14230)]
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
    return static_cast<size_t>( CodecIdx::_COUNT );
}


QString CodecFactory::getCodecTitle(CodecIdx codec_idx) const
{
    return CODEC_DESC[ static_cast<int>(codec_idx) ].title;
}

QString CodecFactory::getCodecKey(CodecIdx codec_idx) const
{
    return CODEC_DESC[ static_cast<int>(codec_idx) ].key;
}

CodecIdx CodecFactory::getCodecIdxByKey(QString codec_key) const
{
    CodecIdx codec_idx = CodecIdx::_COUNT;

    for (
            size_t codec_idx_int = 0;
            codec_idx_int < static_cast<size_t>(CodecIdx::_COUNT);
            ++codec_idx_int
        )
    {
        if (CODEC_DESC[ codec_idx_int ].key == codec_key){
            codec_idx = static_cast<CodecIdx>(codec_idx_int);
            break;
        }
    }

    return codec_idx;
}

std::shared_ptr<Codec> CodecFactory::createCodec(CodecIdx codec_idx) const
{
    std::shared_ptr<Codec> p_ret {};

    switch (codec_idx){
        case CodecIdx::ISO_14230:
            p_ret = std::make_shared<Codec_ISO14230>(codec_idx);
            break;
        case CodecIdx::TRANSPARENT:
            p_ret = std::make_shared<CodecTransparent>(codec_idx);
            break;
        case CodecIdx::_COUNT:
            break;
    }

    if (p_ret == nullptr){
        qDebug("error: no codec was created for number=%d",
                static_cast<int>(codec_idx)
                );
    }

    return p_ret;
}

std::shared_ptr<Codec> CodecFactory::createCodecByKey(QString codec_key) const
{
    return createCodec( getCodecIdxByKey(codec_key) );
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


