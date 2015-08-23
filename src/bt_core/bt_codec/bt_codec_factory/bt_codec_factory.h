/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_FACTORY_H
#define _BT_CODEC_FACTORY_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>

#include "bt_codec_types.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class CodecFactory;
    class Codec;
}

/**
 * TODO
 */
class BTCore::CodecFactory
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/
private:

    struct CodecDesc {
        QString     key;
        QString     title;
    };


    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:



    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    static const CodecDesc CODEC_DESC[];


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/

public:

    size_t getCodecsCnt() const;
    QString getCodecTitle(CodecNum codec_num) const;
    QString getCodecKey(CodecNum codec_num) const;

    CodecNum getCodecNumByKey(QString codec_key) const;

    std::shared_ptr<Codec> createCodec(CodecNum codec_num) const;

    std::shared_ptr<Codec> createCodecByKey(QString codec_key) const;



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_CODEC_FACTORY_H
