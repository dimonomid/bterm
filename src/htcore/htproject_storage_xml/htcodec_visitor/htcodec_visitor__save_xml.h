/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HTCODEC_VISITOR__SAVE_XML_H
#define _HTCODEC_VISITOR__SAVE_XML_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htcodec_visitor.h"

#include <QDomElement>
#include <memory>


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class CodecVisitor_SaveXML;
}

/**
 * TODO
 */
class HTCore::CodecVisitor_SaveXML : public HTCore::CodecVisitor
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

    //-- codec element that was generated during the acceptance
    //   of the visitor
    QDomDocument &doc;
    std::shared_ptr<QDomElement> p_codec_elem;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual void visit(Codec_ISO14230 &) override;

    std::shared_ptr<QDomElement> getDomElement();

};


#endif // _HTCODEC_VISITOR__SAVE_XML_H
