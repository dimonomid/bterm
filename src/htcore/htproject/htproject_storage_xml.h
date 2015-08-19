/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HTPROJECT_STORAGE_XML_H
#define _HTPROJECT_STORAGE_XML_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <QDomElement>
#include <memory>




namespace HTCore {
    class Project;
    class Codec;
    class Codec_ISO14230;
    class ReqHandler;
}

class QIODevice;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class ProjectStorageXML;
}


/**
 * TODO
 */
class HTCore::ProjectStorageXML : public QObject
{
Q_OBJECT

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

    std::shared_ptr<QIODevice> p_device;


    static const QString XML_TAG_NAME__PROJECT;
    static const QString XML_TAG_NAME__CODECS;
    static const QString XML_TAG_NAME__CODEC;
    static const QString XML_TAG_NAME__REQ_HANDLERS;
    static const QString XML_TAG_NAME__REQ_HANDLER;
    static const QString XML_TAG_NAME__RH_CODE;

    static const QString XML_ATTR_NAME__COMMON__NAME;

    static const QString XML_ATTR_NAME__CODEC_ISO14230__LOCAL_ADDR;
    static const QString XML_ATTR_NAME__CODEC_ISO14230__REMOTE_ADDR;

    static const QString CODEC_NAME__ISO14230;

    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:
    /**
     * Read project from QIODevice that was given to constructor.
     */
    std::shared_ptr<Project> readProject();



private:

    QDomElement getSingleChildElementByTagName(
            const QDomElement &elem_parent,
            QString tagName
            );

    std::shared_ptr<Codec> readCodecFromDomElement(
            const QDomElement &elem_codec
            );

    std::shared_ptr<Codec_ISO14230> readCodecIso14230FromDomElement(
            const QDomElement &elem_codec
            );

    std::shared_ptr<ReqHandler> readReqHandlerFromDomElement(
            const QDomElement &elem_rh
            );




    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _HTPROJECT_STORAGE_XML_H
