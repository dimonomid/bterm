/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_TYPES_H
#define _BT_CODEC_TYPES_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>


namespace BTCore {

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /**
     * Codec number, used to identify codecs
     */
    enum class CodecNum {
        /** Transparent (that is, no codec at all: all data is "encoded" and
         * "decoded" literally)
         */
        TRANSPARENT,

        /** ISO 14230
         */
        ISO_14230,

        /** Not actually a number of particular codec, but total count of codecs
         */
        _COUNT
    };

};


#endif // _BT_CODEC_TYPES_H
