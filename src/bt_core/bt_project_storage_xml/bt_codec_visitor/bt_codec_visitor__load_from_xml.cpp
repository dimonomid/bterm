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
    uint8_t fmt_tx = ProjectStorageXML::readUInt8FromElemAttr(
            elem_codec,
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__FMT_TX
            );

    uint8_t local_addr_tx = ProjectStorageXML::readUInt8FromElemAttr(
            elem_codec,
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR_TX
            );

    uint8_t remote_addr_tx = ProjectStorageXML::readUInt8FromElemAttr(
            elem_codec,
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR_TX
            );

    uint8_t fmt_rx = ProjectStorageXML::readUInt8FromElemAttr(
            elem_codec,
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__FMT_RX
            );

    uint8_t local_addr_rx = ProjectStorageXML::readUInt8FromElemAttr(
            elem_codec,
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR_RX
            );

    uint8_t remote_addr_rx = ProjectStorageXML::readUInt8FromElemAttr(
            elem_codec,
            ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR_RX
            );


    codec.setFmtTx(fmt_tx);
    codec.setOwnAddrTx(local_addr_tx);
    codec.setRemoteAddrTx(remote_addr_tx);

    codec.setFmtRx(fmt_rx);
    codec.setOwnAddrRx(local_addr_rx);
    codec.setRemoteAddrRx(remote_addr_rx);
}

void CodecVisitor_LoadFromXML::visit(CodecTransparent &codec)
{
    std::ignore = codec;
}


