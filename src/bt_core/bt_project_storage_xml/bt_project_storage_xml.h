/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_PROJECT_STORAGE_XML_H
#define _BT_PROJECT_STORAGE_XML_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <QDomElement>
#include <memory>




namespace BTCore {
    class Project;
    class Codec;
    class Codec_ISO14230;
    class ReqHandler;
    class IODev;

    class CodecVisitor_SaveXML;
    class CodecVisitor_LoadFromXML;
}

class QIODevice;
class QDomDocument;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class ProjectStorageXML;
}


/**
 * Class that provides loading and saving `#BTCore::Project`
 * from and to an XML format.
 */
class BTCore::ProjectStorageXML : public QObject
{
Q_OBJECT

    friend CodecVisitor_SaveXML;
    friend CodecVisitor_LoadFromXML;

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    ProjectStorageXML(
            std::shared_ptr<QIODevice> p_device
            );

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- IO device to use when reading/saving the project
    std::shared_ptr<QIODevice> p_device;


    static const QString XML_TAG_NAME__PROJECT;
    static const QString XML_TAG_NAME__CODECS;
    static const QString XML_TAG_NAME__CODEC;
    static const QString XML_TAG_NAME__REQ_HANDLERS;
    static const QString XML_TAG_NAME__REQ_HANDLER;
    static const QString XML_TAG_NAME__RH_CODE;
    static const QString XML_TAG_NAME__IODEV;

    static const QString XML_ATTR_NAME__COMMON__TITLE;

    static const QString XML_ATTR_NAME__CODEC__KEY;

    static const QString XML_ATTR_NAME__IODEV__BAUDRATE;

    static const QString XML_ATTR_NAME__CODEC_ISO14230__FMT_TX;
    static const QString XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR_TX;
    static const QString XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR_TX;

    static const QString XML_ATTR_NAME__CODEC_ISO14230__FMT_RX;
    static const QString XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR_RX;
    static const QString XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR_RX;



    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

protected:

    static uint8_t readUInt8FromElemAttr(
            const QDomElement &elem,
            QString attr_name,
            bool throw_if_not_found = true,
            uint8_t def = 0
            );


    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * Read project from QIODevice that was given to the constructor
     *
     * NOTE: in case of error, std::invalid_argument is thrown,
     * so you should be prepared to catch it.
     *
     * @param p_iodev
     *      IO device that project should use. IO parameters
     *      (at least, baudrate) will be loaded from xml as part of
     *      loading process.
     *
     *      But, IO device is NOT set to the project. After project is loaded
     *      and you subscribed on its signals, you need to call
     *      `#BTCore::Project::setIODev()`.
     */
    std::shared_ptr<Project> readProject(
            std::shared_ptr<IODev> p_iodev
            );

    /**
     * Save project to QIODevice that was given to the constructor
     */
    void saveProject(std::shared_ptr<Project> p_proj);


protected:

private:

    QDomElement getSingleChildElementByTagName(
            const QDomElement &elem_parent,
            QString tagName
            );

    std::shared_ptr<Codec> readCodecFromDomElement(
            const QDomElement &elem_codec
            );

    std::shared_ptr<ReqHandler> readReqHandlerFromDomElement(
            const QDomElement &elem_rh
            );


    std::shared_ptr<QDomElement> saveCodecToDomElement(
            QDomDocument &doc, std::shared_ptr<Codec> p_codec
            );

    std::shared_ptr<QDomElement> saveReqHandlerToDomElement(
            QDomDocument &doc, std::shared_ptr<ReqHandler> p_handler
            );

    std::shared_ptr<QDomElement> saveIODevToDomElement(
            QDomDocument &doc, std::shared_ptr<IODev> p_iodev
            );

    void readIODevFromDomElement(
            const QDomElement &elem_codec,
            std::shared_ptr<IODev> p_iodev
            );


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_PROJECT_STORAGE_XML_H
