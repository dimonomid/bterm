/******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_VISITOR_H
#define _BT_CODEC_VISITOR_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec.h"




namespace BTCore {
    class Codec_ISO14230;
    class CodecTransparent;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class CodecVisitor;
}

/**
 * Abstract visitor for `#BTCore::Codec`
 *
 * (if you're unfamiliar with visitor pattern, read about it somewhere; for
 * example, on Wikipedia: https://en.wikipedia.org/wiki/Visitor_pattern )
 */
class BTCore::CodecVisitor
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:

   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:

   virtual void visit(Codec_ISO14230 &) = 0;
   virtual void visit(CodecTransparent &) = 0;

};


#endif // _BT_CODEC_VISITOR_H

