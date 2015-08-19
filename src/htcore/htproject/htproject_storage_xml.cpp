/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htproject_storage_xml.h"




/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const QString ProjectReaderXML::XML_TAG_NAME__PROJECT = "project";
const QString ProjectReaderXML::XML_TAG_NAME__CODECS  = "codecs";
const QString ProjectReaderXML::XML_TAG_NAME__CODEC   = "codec";

const QString ProjectReaderXML::XML_ATTR_NAME__COMMON__NAME     = "name";

const QString ProjectReaderXML::XML_ATTR_NAME__CODEC__ISO14230__LOCAL_ADDR   = "local_addr";
const QString ProjectReaderXML::XML_ATTR_NAME__CODEC__ISO14230__REMOTE_ADDR  = "remote_addr";

const QString ProjectReaderXML::CODEC_NAME__ISO14230   = "iso14230";


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
                    //-- XML file contains more than one codec;
                    //   this is unsupported at the moment. Generate a warning
                    //   and ignore all extra codecs.
                    auto p_event = std::make_shared<EventSys>(
                            EventSys::Level::WARNING,
                            "XML file contains more than one device. "
                            "Having more than one device in the project "
                            "is not supported at the moment. Ignoring all "
                            "devices in XML file except the first one."
                            );
                    emit event(p_event);
                    break;
                }

                p_codec = readCodecFromDomElement(cur_elem);

                ++codecs_cnt;
            }
        }
    }

#if 0
    QDomNode codec_node = elem_proj_attrs.namedItem(
            XML_ATTR_NAME__PROJECT__CODEC
            );
    QString codec_name {};
    std::shared_ptr<Codec> p_codec {};
    if (!codec_node.isNull()){
        //-- codec name specified
        codec_name = codec_node.nodeValue();
        if (codec_name == CODEC_NAME__ISO14230){
            p_codec = std::make_shared<Codec_ISO14230>(
                    0x01, 0x02
                    );
        }
    } else {
        //-- codec name unspecified
        codec_name = QObject::tr("Untitled project");
    }
#endif


    p_proj = std::make_shared<Project>(proj_name);

}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


