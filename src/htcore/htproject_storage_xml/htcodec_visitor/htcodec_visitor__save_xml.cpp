/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htcodec_visitor__save_xml.h"
#include "htproject_storage_xml.h"
#include "htcodec_iso14230.h"



using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

CodecVisitor_SaveXML::CodecVisitor_SaveXML(QDomDocument &doc) :
    doc(doc),
    p_codec_elem()
{
}




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

void CodecVisitor_SaveXML::visit(Codec_ISO14230 &codec)
{
    p_codec_elem = std::make_shared<QDomElement>(
            doc.createElement(ProjectStorageXML::XML_TAG_NAME__CODEC)
            );

    p_codec_elem->setAttribute(
            ProjectStorageXML::XML_ATTR_NAME__COMMON__NAME,
            ProjectStorageXML::CODEC_NAME__ISO14230
            );

    p_codec_elem->setAttribute(
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR,
            "0x" + QString::number(codec.getOwnAddr(), 16)
            );

    p_codec_elem->setAttribute(
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR,
            "0x" + QString::number(codec.getRemoteAddr(), 16)
            );
}

std::shared_ptr<QDomElement> CodecVisitor_SaveXML::getDomElement()
{
    return p_codec_elem;
}

