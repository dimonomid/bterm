/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QTextStream>

#include "bt_project_storage_xml.h"
#include "bt_project.h"
#include "bt_codec.h"
#include "bt_codec_factory.h"
#include "bt_codec_visitor__save_xml.h"
#include "bt_codec_visitor__load_from_xml.h"



using namespace BTCore;

/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const QString ProjectStorageXML::XML_TAG_NAME__PROJECT      = "project";
const QString ProjectStorageXML::XML_TAG_NAME__CODECS       = "codecs";
const QString ProjectStorageXML::XML_TAG_NAME__CODEC        = "codec";
const QString ProjectStorageXML::XML_TAG_NAME__REQ_HANDLERS = "req_handlers";
const QString ProjectStorageXML::XML_TAG_NAME__REQ_HANDLER  = "req_handler";
const QString ProjectStorageXML::XML_TAG_NAME__RH_CODE      = "code";
const QString ProjectStorageXML::XML_TAG_NAME__IODEV        = "iodev";


const QString ProjectStorageXML::XML_ATTR_NAME__COMMON__TITLE = "title";

const QString ProjectStorageXML::XML_ATTR_NAME__CODEC__KEY = "key";

const QString ProjectStorageXML::XML_ATTR_NAME__IODEV__BAUDRATE = "baudrate";

const QString ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__FMT_TX   = "fmt_tx";
const QString ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR_TX   = "local_addr_tx";
const QString ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR_TX  = "remote_addr_tx";

const QString ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__FMT_RX   = "fmt_rx";
const QString ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR_RX   = "local_addr_rx";
const QString ProjectStorageXML::XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR_RX  = "remote_addr_rx";


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

uint8_t ProjectStorageXML::readUInt8FromElemAttr(
        const QDomElement &elem,
        QString attr_name,
        bool throw_if_not_found,
        uint8_t def
        )
{
    uint8_t ret = def;
    bool ok = true;

    QDomNamedNodeMap attrs = elem.attributes();

    QDomNode node = attrs.namedItem(attr_name);
    if (node.isNull()){
        if (throw_if_not_found){
            throw std::invalid_argument(std::string("line ")
                    + QString::number(elem.lineNumber()).toStdString()
                    + ": no attr \"" + attr_name.toStdString() + "\""
                    );
        }
    } else {
        //-- try to parse
        unsigned int value_int = node.nodeValue().toUInt(
                &ok, 0
                );
        if (!ok){
            throw std::invalid_argument(std::string("line ")
                    + QString::number(elem.lineNumber()).toStdString()
                    + ": error parsing uint8_t from "
                    + "\"" + node.nodeValue().toStdString() + "\""
                    );
        }

        //-- check if it is too large
        if (value_int > 0xff){
            throw std::invalid_argument(std::string("line ")
                    + QString::number(elem.lineNumber()).toStdString()
                    + ": wrong value of attr: "
                    + "\"" + node.nodeValue().toStdString() + "\""
                    + ", it must be from 0 to 0xff"
                    );
        }

        ret = value_int;
    }

    return ret;
}


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
    QDomNode codec_key_node = elem_codec_attrs.namedItem(
            XML_ATTR_NAME__CODEC__KEY
            );

    if (codec_key_node.isNull()){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": no key specified for codec"
                );
    }

    QString codec_key = codec_key_node.nodeValue();

    {
        CodecFactory factory {};
        p_codec = factory.createCodecByKey(codec_key);
    }

    //TODO: use factory
    if (p_codec == nullptr){
        throw std::invalid_argument(std::string("line ")
                + QString::number(elem_codec.lineNumber()).toStdString()
                + ": unsupported codec specified: "
                + "\"" + codec_key.toStdString() + "\""
                );
    }

    {
        CodecVisitor_LoadFromXML codec_visitor_load_from_xml {elem_codec};
        p_codec->accept(codec_visitor_load_from_xml);
    }

    return p_codec;
}


std::shared_ptr<ReqHandler> ProjectStorageXML::readReqHandlerFromDomElement(
        const QDomElement &elem_rh
        )
{
    std::shared_ptr<ReqHandler> p_rh {};

    QDomNamedNodeMap elem_rh_attrs = elem_rh.attributes();
    QDomNode rh_name_node = elem_rh_attrs.namedItem(
            XML_ATTR_NAME__COMMON__TITLE
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

std::shared_ptr<QDomElement> ProjectStorageXML::saveCodecToDomElement(
        QDomDocument &doc, std::shared_ptr<Codec> p_codec
        )
{
    CodecVisitor_SaveXML codec_visitor_save_xml {doc};
    p_codec->accept(codec_visitor_save_xml);

    return codec_visitor_save_xml.getDomElement();
}

std::shared_ptr<QDomElement> ProjectStorageXML::saveReqHandlerToDomElement(
        QDomDocument &doc, std::shared_ptr<ReqHandler> p_handler
        )
{
    std::shared_ptr<QDomElement> p_handler_elem =
        std::make_shared<QDomElement>(
                doc.createElement(XML_TAG_NAME__REQ_HANDLER)
                );

    //-- set handler name
    p_handler_elem->setAttribute(
            ProjectStorageXML::XML_ATTR_NAME__COMMON__TITLE,
            p_handler->getTitle()
            );

    //-- create code element
    {
        QDomElement code_elem = doc.createElement(
                XML_TAG_NAME__RH_CODE
                );

        QDomText code_text_node = doc.createTextNode(p_handler->getScript());
        code_elem.appendChild(code_text_node);

        p_handler_elem->appendChild(code_elem);
    }

    return p_handler_elem;
}

std::shared_ptr<QDomElement> ProjectStorageXML::saveIODevToDomElement(
        QDomDocument &doc, std::shared_ptr<IODev> p_iodev
        )
{
    std::shared_ptr<QDomElement> p_iodev_elem =
        std::make_shared<QDomElement>(
                doc.createElement(XML_TAG_NAME__IODEV)
                );

    //-- set handler name
    p_iodev_elem->setAttribute(
            ProjectStorageXML::XML_ATTR_NAME__IODEV__BAUDRATE,
            QString::number(p_iodev->getBaudRate())
            );

    return p_iodev_elem;
}

void ProjectStorageXML::readIODevFromDomElement(
        const QDomElement &iodev_elem,
        std::shared_ptr<IODev> p_iodev
        )
{
    bool ok = true;

    QDomNamedNodeMap attrs = iodev_elem.attributes();

    QDomNode node = attrs.namedItem(XML_ATTR_NAME__IODEV__BAUDRATE);

    if (node.isNull()){
        throw std::invalid_argument(std::string("line ")
                + QString::number(iodev_elem.lineNumber()).toStdString()
                + ": no attr \"" + XML_ATTR_NAME__IODEV__BAUDRATE.toStdString() + "\""
                );
    }

    //-- try to parse
    unsigned int baudrate = node.nodeValue().toUInt(
            &ok, 0
            );
    if (!ok){
        throw std::invalid_argument(std::string("line ")
                + QString::number(iodev_elem.lineNumber()).toStdString()
                + ": error parsing baudrate value from "
                + "\"" + node.nodeValue().toStdString() + "\""
                );
    }

    p_iodev->setBaudRate(baudrate);
}



/* protected    */




/* public       */

std::shared_ptr<Project> ProjectStorageXML::readProject(
        std::shared_ptr<IODev> p_iodev
        )
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
            XML_ATTR_NAME__COMMON__TITLE
            );
    QString proj_name {};
    if (!proj_name_node.isNull()){
        //-- project name specified
        proj_name = proj_name_node.nodeValue();
    } else {
        //-- project name unspecified
        proj_name = QObject::tr("Untitled project");
    }

    //-- now, since we have title, we can create the project
    p_proj = std::make_shared<Project>(proj_name);


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

    //-- hanlde iodev
    {

        QDomElement iodev_elem = getSingleChildElementByTagName(
                elem_proj, XML_TAG_NAME__IODEV
                );

        readIODevFromDomElement(iodev_elem, p_iodev);
    }


    //-- add known codec to project and immediately set it as an active codec
    p_proj->addKnownCodec(p_codec);
    p_proj->setCurrentCodecNum(p_codec->getCodecNum());

    //-- read handlers
    {

        QDomElement handlers_folder = getSingleChildElementByTagName(
                elem_proj,
                XML_TAG_NAME__REQ_HANDLERS
                );

        //-- get rh nodes (currently, there should be just one codec)
        QDomNodeList rh_nodes = handlers_folder.elementsByTagName(
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

void ProjectStorageXML::saveProject(std::shared_ptr<Project> p_proj)
{
    QDomDocument doc("");

    //-- create root project element
    QDomElement project_elem = doc.createElement(XML_TAG_NAME__PROJECT);
    doc.appendChild(project_elem);

    //-- save project name
    project_elem.setAttribute(
            ProjectStorageXML::XML_ATTR_NAME__COMMON__TITLE,
            p_proj->getTitle()
            );

    //-- save codec
    {
        //-- create codecs folder
        QDomElement codecs_folder_elem = doc.createElement(XML_TAG_NAME__CODECS);
        project_elem.appendChild(codecs_folder_elem);

        //-- create codec element inside
        std::shared_ptr<Codec> p_codec = p_proj->getCodec();

        std::shared_ptr<QDomElement> p_codec_elem =
            saveCodecToDomElement(doc, p_codec);

        codecs_folder_elem.appendChild(*p_codec_elem);
    }

    //-- save iodev
    {
        std::shared_ptr<IODev> p_iodev = p_proj->getIODev();

        //-- create iodev element
        std::shared_ptr<QDomElement> p_iodev_elem =
            saveIODevToDomElement(doc, p_iodev);

        project_elem.appendChild(*p_iodev_elem);
    }

    //-- save headers
    {
        //-- create rhs folder
        QDomElement rhs_folder_elem = doc.createElement(XML_TAG_NAME__REQ_HANDLERS);
        project_elem.appendChild(rhs_folder_elem);

        size_t handlers_cnt = p_proj->getHandlersCnt();

        for (size_t i = 0; i < handlers_cnt; i++){
            std::shared_ptr<ReqHandler> p_handler =
                p_proj->getHandler(i);

            std::shared_ptr<QDomElement> p_handler_elem =
                saveReqHandlerToDomElement(doc, p_handler);

            rhs_folder_elem.appendChild(*p_handler_elem);
        }
    }




    //-- add xml header
    {
        QDomNode xml_node = doc.createProcessingInstruction(
                "xml",
                "version=\"1.0\" encoding=\"UTF-8\""
                );
        doc.insertBefore(xml_node, doc.firstChild());
    }

    //-- save xml data
    QTextStream out( p_device.get() );
    doc.save(out, 4);
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


