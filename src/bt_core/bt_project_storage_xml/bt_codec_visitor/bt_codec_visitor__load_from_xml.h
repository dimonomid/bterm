/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_VISITOR__LOAD_FROM_XML_H
#define _BT_CODEC_VISITOR__LOAD_FROM_XML_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec_visitor.h"

#include <QDomElement>
#include <memory>


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class CodecVisitor_LoadFromXML;
}

/**
 * Concrete visitor for `#BTCore::Codec`, it implements `loadFromXML` functionality.
 */
class BTCore::CodecVisitor_LoadFromXML : public BTCore::CodecVisitor
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    CodecVisitor_LoadFromXML(
            const QDomElement &elem_codec
            );


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- `QDomElement` given to constructor (it contains actual data to read)
    const QDomElement &elem_codec;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual void visit(Codec_ISO14230 &) override;
    virtual void visit(CodecTransparent &) override;

};


#endif // _BT_CODEC_VISITOR__LOAD_FROM_XML_H
