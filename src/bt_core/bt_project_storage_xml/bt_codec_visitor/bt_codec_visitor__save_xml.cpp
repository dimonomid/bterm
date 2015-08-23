/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec_visitor__save_xml.h"
#include "bt_project_storage_xml.h"
#include "bt_codec_iso14230.h"
#include "bt_codec_factory.h"



using namespace BTCore;

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
    CodecFactory factory;

    p_codec_elem = std::make_shared<QDomElement>(
            doc.createElement(ProjectStorageXML::XML_TAG_NAME__CODEC)
            );

    p_codec_elem->setAttribute(
            ProjectStorageXML::XML_ATTR_NAME__CODEC__KEY,
            factory.getCodecKey(CodecNum::ISO_14230)
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

void CodecVisitor_SaveXML::visit(CodecTransparent &codec)
{
    std::ignore = codec;
    CodecFactory factory;

    p_codec_elem = std::make_shared<QDomElement>(
            doc.createElement(ProjectStorageXML::XML_TAG_NAME__CODEC)
            );

    p_codec_elem->setAttribute(
            ProjectStorageXML::XML_ATTR_NAME__CODEC__KEY,
            factory.getCodecKey(CodecNum::TRANSPARENT)
            );
}


std::shared_ptr<QDomElement> CodecVisitor_SaveXML::getDomElement()
{
    return p_codec_elem;
}

