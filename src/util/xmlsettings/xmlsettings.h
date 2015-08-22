/******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef __XML_SETTINGS_H__
#define __XML_SETTINGS_H__

/******************************************************************************************
 * INCLUDED FILES
 *****************************************************************************************/

#include <QString>
#include <QSettings>

#include <memory>


class QDomDocument;
class QDomElement;
class QIODevice;



/******************************************************************************************
 * CLASS DECLARATION
 *****************************************************************************************/

/**
 * Class that provides setting storage in XML format.
 *
 * Original code taken a long ago from http://www.prog.org.ru/topic_12074_0.bt_ml
 */
class XmlSettings
{

    /******************************************************************************************
     * TYPES
     *****************************************************************************************/

    /******************************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     *****************************************************************************************/
public:
    explicit XmlSettings( QString fname = "" );


    /******************************************************************************************
     * PRIVATE DATA
     *****************************************************************************************/
private:
    std::shared_ptr<QSettings> p_settings;

    static const QString XML_TAG_NAME__ROOT;

    static const QString XML_ATTR_NAME__ITEM__VALUE;

    /******************************************************************************************
     * STATIC METHODS
     *****************************************************************************************/
private:
    static bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map);
    static bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map);
    static void processWriteKey( QDomDocument& doc, QDomElement& domElement, QString key, const QVariant& value );
    static void processReadKey( QString key, QSettings::SettingsMap &map, QDomElement& domElement );

    /*
     * Following 3 functions are copied from Qt src/corelib/io/qsettings.cpp
     */
    static QString  variantToString(const QVariant &v);
    static QVariant stringToVariant(const QString  &s);
    static QStringList splitArgs(const QString &s, int idx);


    /******************************************************************************************
     * METHODS
     *****************************************************************************************/
public:

    inline QSettings& settings() const { return *p_settings; }

    // при использовании XmlSettings::value конфиг создастся автоматически, если его не было
    QVariant value( const QString & key, const QVariant & defaultValue = QVariant() );
    void setValue ( const QString & key, const QVariant & value );



    /******************************************************************************************
     * SIGNALS, SLOTS
     *****************************************************************************************/

};

#endif // __XML_SETTINGS_H__
