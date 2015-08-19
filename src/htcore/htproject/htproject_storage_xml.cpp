/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htproject_storage_xml.h"
#include "htproject.h"
#include "htcodec.h"
#include "htcodec_iso14230.h"



using namespace HTCore;

/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const QString ProjectStorageXML::XML_TAG_NAME__PROJECT = "project";
const QString ProjectStorageXML::XML_TAG_NAME__CODECS  = "codecs";
const QString ProjectStorageXML::XML_TAG_NAME__CODEC   = "codec";
const QString ProjectStorageXML::XML_TAG_NAME__REQ_HANDLERS = "req_handlers";
const QString ProjectStorageXML::XML_TAG_NAME__REQ_HANDLER  = "req_handler";
const QString ProjectStorageXML::XML_TAG_NAME__RH_CODE  = "code";


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

QDomElement ProjectStorageXML::getSingleChildElementByTagName(
        const QDomElement &elem_parent,
        QString tagName
        )
{
    QDomNodeList rh_folders = elem_parent.elementsByTagName(tagName);

    //-- there should be exactly one folder
    if (rh_folders.count() != 1){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_parent.lineNumber()).toStdString()
                + ": there should be exactly one \""
                + tagName.toStdString()
                + "\" element, but actual count is: "
                + QString::number(rh_folders.count()).toStdString()
                );
    }

    if (rh_folders.item(0).nodeType() != QDomNode::ElementNode){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_parent.lineNumber()).toStdString()
                + ": wrong node type (Element expected)"
                );
    }

    return rh_folders.item(0).toElement();
}

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

    //-- make sure both addresses are specified
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

    //-- try to parse addresses
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

    //-- check that addresses aren't too large
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


std::shared_ptr<ReqHandler> ProjectStorageXML::readReqHandlerFromDomElement(
        const QDomElement &elem_rh
        )
{
    std::shared_ptr<ReqHandler> p_rh {};

    QDomNamedNodeMap elem_rh_attrs = elem_rh.attributes();
    QDomNode rh_name_node = elem_rh_attrs.namedItem(
            XML_ATTR_NAME__COMMON__NAME
            );

    QString rh_name {};
    if (!rh_name_node.isNull()){
        rh_name = rh_name_node.nodeValue();
    }

    //-- get code elem
    QDomElement code_elem = getSingleChildElementByTagName(
            elem_rh,
            XML_TAG_NAME__RH_CODE
            );
    QString code = code_elem.text();

    p_rh = std::make_shared<ReqHandler>(
            rh_name, code
            );

    return p_rh;
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

    //-- handle codec
    std::shared_ptr<Codec> p_codec {};
    {
        //-- get codecs folder
        QDomElement codecs_folder = getSingleChildElementByTagName(
                elem_proj,
                XML_TAG_NAME__CODECS
                );

        //-- get codec nodes (currently, there should be just one codec)
        QDomNodeList codec_nodes = codecs_folder.elementsByTagName(
                XML_TAG_NAME__CODEC
                );

        int codecs_cnt = 0;

        for (int i = 0; i < codec_nodes.count(); ++i){
            QDomNode cur_node = codec_nodes.item(i);
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

                //-- read codec
                p_codec = readCodecFromDomElement(cur_elem);

                ++codecs_cnt;
            }
        }
    }


    //-- now, since we have codec, we can create the project
    p_proj = std::make_shared<Project>(p_codec);

    //TODO: read handlers
    {
        //-- get handlers folder
        QDomNodeList rh_folders = elem_proj.elementsByTagName(
                XML_TAG_NAME__REQ_HANDLERS
                );
        //-- there should be exactly one folder
        if (rh_folders.count() != 1){
            throw std::invalid_argument(std::string("line ")
                    + QString::number(elem_proj.lineNumber()).toStdString()
                    + ": there should be exactly one \""
                    + XML_TAG_NAME__REQ_HANDLERS.toStdString()
                    + "\" element, but actual count is: "
                    + QString::number(rh_folders.count()).toStdString()
                    );
        }

        if (rh_folders.item(0).nodeType() != QDomNode::ElementNode){
            throw std::invalid_argument(std::string("line ")
                    + QString::number(elem_proj.lineNumber()).toStdString()
                    + ": wrong node type (Element expected)"
                    );
        }

        //-- get rh nodes (currently, there should be just one codec)
        QDomNodeList rh_nodes = rh_folders.item(0).toElement().elementsByTagName(
                XML_TAG_NAME__REQ_HANDLER
                );


        for (int i = 0; i < rh_nodes.count(); ++i){
            QDomNode cur_node = rh_nodes.item(i);
            if (cur_node.nodeType() == QDomNode::ElementNode){
                QDomElement cur_elem = cur_node.toElement();
                //-- since we've used elementsByTagName(),
                //   we're sure that tag name is correct

                //-- read rh
                std::shared_ptr<ReqHandler> p_rh
                    = readReqHandlerFromDomElement(cur_elem);

                p_proj->addHandler(p_rh);
            }
        }
    }


    return p_proj;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


