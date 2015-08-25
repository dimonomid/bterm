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
 * Factory that creates `#BTCore::Codec` by codec index (see
 * `#BTCore::CodecIdx`).
 */
class BTCore::CodecFactory
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/
private:

    /**
     * Codec descriptor: contains unique string key to be stored in XML and
     * human-readable title.
     */
    struct CodecDesc {
        /** unique codec key, stored in XML
         */
        QString     key;

        /** human-readable title
         */
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

    /** Array of codec descriptors, there is a descriptor for each available
     * codec (see `#BTCore::CodecIdx`)
     */
    static const CodecDesc CODEC_DESC[];



    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/

public:

    /**
     * Returns total count of codecs (basically, returns
     * `#BTCore::CodecIdx::_COUNT`)
     */
    size_t getCodecsCnt() const;

    /**
     * Returns human-readable codec title by codec index (see
     * `#BTCore::CodecIdx`)
     */
    QString getCodecTitle(CodecIdx codec_idx) const;

    /**
     * Returns unique codec string key by codec index (see `#BTCore::CodecIdx`)
     */
    QString getCodecKey(CodecIdx codec_idx) const;

    /**
     * Returns codec index by its unique string key (needed when loading
     * project from XML file)
     */
    CodecIdx getCodecIdxByKey(QString codec_key) const;

    /**
     * Create codec by its index
     */
    std::shared_ptr<Codec> createCodec(CodecIdx codec_idx) const;

    /**
     * Create codec by its unique string key
     */
    std::shared_ptr<Codec> createCodecByKey(QString codec_key) const;



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_CODEC_FACTORY_H
