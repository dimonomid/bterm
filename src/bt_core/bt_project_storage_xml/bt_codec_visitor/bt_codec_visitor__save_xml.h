/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_VISITOR__SAVE_XML_H
#define _BT_CODEC_VISITOR__SAVE_XML_H

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
    class CodecVisitor_SaveXML;
}

/**
 * Concrete visitor for `#BTCore::Codec`, it implements `saveXML` functionality.
 */
class BTCore::CodecVisitor_SaveXML : public BTCore::CodecVisitor
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    CodecVisitor_SaveXML(QDomDocument &doc);


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- `QDomDocument` given to constructor
    QDomDocument &doc;

    //-- codec element that was generated during the acceptance
    //   of the visitor. Returned by `getDomElement()`
    std::shared_ptr<QDomElement> p_codec_elem;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual void visit(Codec_ISO14230 &) override;

    /**
     * Returns element that was generated during the acceptance of the visitor.
     */
    std::shared_ptr<QDomElement> getDomElement();

};


#endif // _BT_CODEC_VISITOR__SAVE_XML_H
