/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec_visitor__load_from_xml.h"
#include "bt_project_storage_xml.h"
#include "bt_codec_iso14230.h"



using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

CodecVisitor_LoadFromXML::CodecVisitor_LoadFromXML(
        const QDomElement &elem_codec
        ) :
    elem_codec(elem_codec)
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

void CodecVisitor_LoadFromXML::visit(Codec_ISO14230 &codec)
{
    bool ok = true;

    QDomNamedNodeMap elem_codec_attrs = elem_codec.attributes();
    QDomNode codec_local_addr_node = elem_codec_attrs.namedItem(
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR
            );
    QDomNode codec_remote_addr_node = elem_codec_attrs.namedItem(
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR
            );

    //-- make sure both addresses are specified
    if (codec_local_addr_node.isNull()){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": no local addr specified for codec iso14230"
                );
    }

    if (codec_remote_addr_node.isNull()){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": no remote addr specified for codec iso14230"
                );
    }

    //-- try to parse addresses
    unsigned int local_addr_int = codec_local_addr_node.nodeValue().toUInt(
            &ok, 0
            );
    if (!ok){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": error parsing local addr "
                + "\"" + codec_local_addr_node.nodeValue().toStdString() + "\""
                );
    }

    unsigned int remote_addr_int = codec_remote_addr_node.nodeValue().toUInt(
            &ok, 0
            );
    if (!ok){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": error parsing remote addr "
                + "\"" + codec_remote_addr_node.nodeValue().toStdString() + "\""
                );
    }

    //-- check that addresses aren't too large
    if (local_addr_int > 0xff){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": wrong local addr given: "
                + "\"" + codec_local_addr_node.nodeValue().toStdString() + "\""
                + ", it must be from 0 to 0xff"
                );
    }

    if (remote_addr_int > 0xff){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": wrong remote addr given: "
                + "\"" + codec_remote_addr_node.nodeValue().toStdString() + "\""
                + ", it must be from 0 to 0xff"
                );
    }

    codec.setOwnAddr(local_addr_int);
    codec.setRemoteAddr(remote_addr_int);
}

void CodecVisitor_LoadFromXML::visit(CodecTransparent &codec)
{
    std::ignore = codec;
}


