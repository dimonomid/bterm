/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htproject_storage_xml.h"
#include "htcodec.h"
#include "htcodec_iso14230.h"



using namespace HTCore;

/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const QString ProjectStorageXML::XML_TAG_NAME__PROJECT = "project";
const QString ProjectStorageXML::XML_TAG_NAME__CODECS  = "codecs";
const QString ProjectStorageXML::XML_TAG_NAME__CODEC   = "codec";

const QString ProjectStorageXML::XML_ATTR_NAME__COMMON__NAME     = "name";

const QString ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR   = "local_addr";
const QString ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR  = "remote_addr";

const QString ProjectStorageXML::CODEC_NAME__ISO14230   = "iso14230";


/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ProjectStorageXML::ProjectStorageXML(
        std::shared_ptr<QIODevice> p_device
        ) :
    p_device(p_device)
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

std::shared_ptr<Codec> ProjectStorageXML::readCodecFromDomElement(
        const QDomElement &elem_codec
        )
{
    std::shared_ptr<Codec> p_codec {};

    QDomNamedNodeMap elem_codec_attrs = elem_codec.attributes();
    QDomNode codec_name_node = elem_codec_attrs.namedItem(
            XML_ATTR_NAME__COMMON__NAME
            );

    if (codec_name_node.isNull()){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": no name specified for codec"
                );
    }

    QString codec_name = codec_name_node.nodeValue();

    if (codec_name == CODEC_NAME__ISO14230){
        p_codec = readCodecIso14230FromDomElement(elem_codec);
    } else {
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": unsupported codec specified: "
                + "\"" + codec_name.toStdString() + "\""
                );
    }

    return p_codec;
}

/**
 * Read Codec_ISO14230 from dom element. This function is called only
 * by readCodecFromDomElement(), which first determines the codec name.
 */
std::shared_ptr<Codec_ISO14230> ProjectStorageXML::readCodecIso14230FromDomElement(
        const QDomElement &elem_codec_iso14230
        )
{
    bool ok = true;

    std::shared_ptr<Codec_ISO14230> p_codec {};

    QDomNamedNodeMap elem_codec_attrs = elem_codec_iso14230.attributes();
    QDomNode codec_local_addr_node = elem_codec_attrs.namedItem(
            XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR
            );
    QDomNode codec_remote_addr_node = elem_codec_attrs.namedItem(
            XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR
            );

    if (codec_local_addr_node.isNull()){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec_iso14230.lineNumber()).toStdString()
                + ": no local addr specified for codec iso14230"
                );
    }

    if (codec_remote_addr_node.isNull()){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec_iso14230.lineNumber()).toStdString()
                + ": no remote addr specified for codec iso14230"
                );
    }

    unsigned int local_addr_int = codec_local_addr_node.nodeValue().toUInt(
            &ok, 0
            );
    if (!ok){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec_iso14230.lineNumber()).toStdString()
                + ": error parsing local addr "
                + "\"" + codec_local_addr_node.nodeValue().toStdString() + "\""
                );
    }

    unsigned int remote_addr_int = codec_remote_addr_node.nodeValue().toUInt(
            &ok, 0
            );
    if (!ok){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec_iso14230.lineNumber()).toStdString()
                + ": error parsing remote addr "
                + "\"" + codec_remote_addr_node.nodeValue().toStdString() + "\""
                );
    }

    if (local_addr_int > 0xff){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec_iso14230.lineNumber()).toStdString()
                + ": wrong local addr given: "
                + "\"" + codec_local_addr_node.nodeValue().toStdString() + "\""
                + ", it must be from 0 to 0xff"
                );
    }

    if (remote_addr_int > 0xff){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec_iso14230.lineNumber()).toStdString()
                + ": wrong remote addr given: "
                + "\"" + codec_remote_addr_node.nodeValue().toStdString() + "\""
                + ", it must be from 0 to 0xff"
                );
    }

    //-- after all, create the codec
    p_codec = std::make_shared<Codec_ISO14230>(
            local_addr_int,
            remote_addr_int
            );

    return p_codec;
}


/* protected    */

/* public       */

std::shared_ptr<Project> ProjectStorageXML::readProject()
{
    std::shared_ptr<Project> p_proj {};

    QString error_msg;
    int error_line = 0;
    int error_col = 0;

    QDomDocument doc {};
    if (!doc.setContent(p_device.get(), &error_msg, &error_line, &error_col)){
        throw std::invalid_argument(std::string("line ")
                + QString::number(error_line).toStdString()
                + ", col " + QString::number(error_col).toStdString()
                + ": " + error_msg.toStdString()
                );
    }

    //-- get root element of the document (should be XML_TAG_NAME__PROJECT)
    QDomElement elem_proj = doc.documentElement();
    if (elem_proj.tagName() != XML_TAG_NAME__PROJECT){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_proj.lineNumber()).toStdString()
                + ": root tag name should be \""
                + XML_TAG_NAME__PROJECT.toStdString()
                + "\", but it is \""
                + elem_proj.tagName().toStdString()
                + "\""
                );
    }

    //-- tag name is correct, so, proceed: get project name
    QDomNamedNodeMap elem_proj_attrs = elem_proj.attributes();
    QDomNode proj_name_node = elem_proj_attrs.namedItem(
            XML_ATTR_NAME__COMMON__NAME
            );
    QString proj_name {};
    if (!proj_name_node.isNull()){
        //-- project name specified
        proj_name = proj_name_node.nodeValue();
    } else {
        //-- project name unspecified
        proj_name = QObject::tr("Untitled project");
    }

    //-- handle codecs
    std::shared_ptr<Codec> p_codec {};
    {
        QDomNodeList children = elem_proj.elementsByTagName(
                XML_TAG_NAME__CODEC
                );

        int codecs_cnt = 0;

        for (int i = 0; i < children.count(); ++i){
            QDomNode cur_node = children.item(i);
            if (cur_node.nodeType() == QDomNode::ElementNode){
                QDomElement cur_elem = cur_node.toElement();
                //-- since we've used elementsByTagName(),
                //   we're sure that tag name is correct

                if (codecs_cnt > 0){
                    //TODO
#if 0
                    //-- XML file contains more than one codec;
                    //   this is unsupported at the moment. Generate a warning
                    //   and ignore all extra codecs.
                    auto p_event = std::make_shared<EventSys>(
                            EventSys::Level::WARNING,
                            "XML file contains more than one codec. "
                            "Having more than one codec in the project "
                            "is not supported at the moment. Ignoring all "
                            "codec in XML file except the first one."
                            );
                    emit event(p_event);
#endif
                    break;
                }

                p_codec = readCodecFromDomElement(cur_elem);

                ++codecs_cnt;
            }
        }
    }


    p_proj = std::make_shared<Project>(p_codec);

    return p_proj;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


