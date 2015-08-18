/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************************
 * INCLUDED FILES
 *****************************************************************************************/


#include "xmlsettings.h"
#include <QDomDocument>
#include <QDebug>

#include <QDataStream>
#include <QRect>
#include <QSize>
#include <QByteArray>
#include <QStringList>



/******************************************************************************************
 * PRIVATE DATA
 *****************************************************************************************/

const QString XmlSettings::XML_TAG_NAME__ROOT = "root";

const QString XmlSettings::XML_ATTR_NAME__ITEM__VALUE = "value";

/******************************************************************************************
 * DEFINITIONS
 *****************************************************************************************/

/******************************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 *****************************************************************************************/

/* public       */

XmlSettings::XmlSettings( QString fname )
{
   if ( fname.isEmpty() ){
      fname = "noname.xml";
   }
   
   static const QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
   
   p_settings = std::shared_ptr<QSettings>(new QSettings( fname, XmlFormat ));
}





/******************************************************************************************
 * STATIC METHODS
 *****************************************************************************************/

/* private      */

bool XmlSettings::readXmlFile(QIODevice &device, QSettings::SettingsMap &map)
{

   QDomDocument doc("");
   if ( !doc.setContent( &device ) ) return false;

   //-- get the root element of the document (which is XML_TAG_NAME__ROOT actually)
   QDomElement root = doc.documentElement();

   //-- handle all the root children
   {
      QDomNodeList children = root.childNodes();

      for (int i = 0; i < children.count(); ++i){
         QDomElement currentChild = children.item(i).toElement();
         processReadKey("", map, currentChild);
      }
   }

   return true;
}

bool XmlSettings::writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map)
{

   QDomDocument doc("");
   QDomElement root = doc.createElement(XML_TAG_NAME__ROOT);
   doc.appendChild(root);

   QMapIterator<QString, QVariant> i(map);
   while ( i.hasNext() )
   {
      i.next();

      QString  sKey = i.key();
      QVariant value = i.value();
      processWriteKey( doc, root, sKey, i.value() );
   };

   QDomNode xmlNode = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\""); 
   doc.insertBefore(xmlNode, doc.firstChild());

   QTextStream out( &device );
   doc.save(out, 3);

   return true;
}

void XmlSettings::processWriteKey( QDomDocument& doc, QDomElement& domElement, QString key, const QVariant& value )
{

   int slashPos = key.indexOf( '/' );

   if (slashPos < 0){
      //-- given key is a param (not folder)

      QDomElement item_element = doc.createElement(key);

      item_element.setAttribute(XML_ATTR_NAME__ITEM__VALUE, XmlSettings::variantToString(value));

      domElement.appendChild(item_element);

   } else {
      //-- given key is a folder

      //-- get the name of the group for appropriate xml node
      QString groupName = key.left( slashPos );

      //-- get/create node for the key
      QDomElement groupElement;

      QDomNode foundGroupNode = domElement.namedItem( groupName );

      if ( foundGroupNode.isNull() ){

         groupElement = doc.createElement( groupName );

         domElement.appendChild( groupElement );
      } else {
         groupElement = foundGroupNode.toElement();
      }

      //-- create truncated part of the key
      key = key.right( key.size() - slashPos - 1 );

      //-- continue handling (creation/looking_for groups),
      //   until it is eventually succeed
      processWriteKey( doc, groupElement, key, value );
   }

}

void XmlSettings::processReadKey( QString parentKey, QSettings::SettingsMap &map, QDomElement& domElement )
{

   QString currentKey = parentKey + domElement.tagName();
   QString currentKeyForChildren = currentKey + "/";

   QDomNamedNodeMap namedNodeMap = domElement.attributes();
   QDomNode value_node = namedNodeMap.namedItem(XML_ATTR_NAME__ITEM__VALUE);

   if (!value_node.isNull()){
      //-- value is set for this item. Let's add it to the resulting map.

      map.insert(currentKey, stringToVariant(value_node.nodeValue()));

   }


   //-- handle all the children
   {
      QDomNodeList children = domElement.childNodes();

      for (int i = 0; i < children.count(); ++i){
         QDomElement currentChild = children.item(i).toElement();
         processReadKey(currentKeyForChildren, map, currentChild);
      }
   }



}


/**
 * This function is copied from Qt src/corelib/io/qsettings.cpp
 */
QString XmlSettings::variantToString(const QVariant &v)
{
   QString result;

   switch (v.type()) {
      case QVariant::Invalid:
         result = QLatin1String("@Invalid()");
         break;

      case QVariant::ByteArray: {
                                   QByteArray a = v.toByteArray();
                                   result = QLatin1String("@ByteArray(");
                                   result += QString::fromLatin1(a.constData(), a.size());
                                   result += QLatin1Char(')');
                                   break;
                                }

      case QVariant::String:
      case QVariant::LongLong:
      case QVariant::ULongLong:
      case QVariant::Int:
      case QVariant::UInt:
      case QVariant::Bool:
      case QVariant::Double:
      case QVariant::KeySequence: {
                                     result = v.toString();
                                     if (result.startsWith(QLatin1Char('@')))
                                        result.prepend(QLatin1Char('@'));
                                     break;
                                  }
      case QVariant::Rect: {
                              QRect r = qvariant_cast<QRect>(v);
                              result += QLatin1String("@Rect(");
                              result += QString::number(r.x());
                              result += QLatin1Char(' ');
                              result += QString::number(r.y());
                              result += QLatin1Char(' ');
                              result += QString::number(r.width());
                              result += QLatin1Char(' ');
                              result += QString::number(r.height());
                              result += QLatin1Char(')');
                              break;
                           }
      case QVariant::Size: {
                              QSize s = qvariant_cast<QSize>(v);
                              result += QLatin1String("@Size(");
                              result += QString::number(s.width());
                              result += QLatin1Char(' ');
                              result += QString::number(s.height());
                              result += QLatin1Char(')');
                              break;
                           }
      case QVariant::Point: {
                               QPoint p = qvariant_cast<QPoint>(v);
                               result += QLatin1String("@Point(");
                               result += QString::number(p.x());
                               result += QLatin1Char(' ');
                               result += QString::number(p.y());
                               result += QLatin1Char(')');
                               break;
                            }

      default: {
                  QByteArray a;
                  {
                     QDataStream s(&a, QIODevice::WriteOnly);
                     s.setVersion(QDataStream::Qt_4_0);
                     s << v;
                  }

                  result = QLatin1String("@Variant(");
                  result += QString::fromLatin1(a.constData(), a.size());
                  result += QLatin1Char(')');
                  break;
               }
   }

   return result;
}


/**
 * This function is copied from Qt src/corelib/io/qsettings.cpp
 */
QVariant XmlSettings::stringToVariant(const QString &s)
{
   if (s.startsWith(QLatin1Char('@'))) {
      if (s.endsWith(QLatin1Char(')'))) {
         if (s.startsWith(QLatin1String("@ByteArray("))) {
            return QVariant(s.toLatin1().mid(11, s.size() - 12));
         } else if (s.startsWith(QLatin1String("@Variant("))) {
            QByteArray a(s.toLatin1().mid(9));
            QDataStream stream(&a, QIODevice::ReadOnly);
            stream.setVersion(QDataStream::Qt_4_0);
            QVariant result;
            stream >> result;
            return result;
         } else if (s.startsWith(QLatin1String("@Rect("))) {
            QStringList args = XmlSettings::splitArgs(s, 5);
            if (args.size() == 4)
               return QVariant(QRect(args[0].toInt(), args[1].toInt(), args[2].toInt(), args[3].toInt()));
         } else if (s.startsWith(QLatin1String("@Size("))) {
            QStringList args = XmlSettings::splitArgs(s, 5);
            if (args.size() == 2)
               return QVariant(QSize(args[0].toInt(), args[1].toInt()));
         } else if (s.startsWith(QLatin1String("@Point("))) {
            QStringList args = XmlSettings::splitArgs(s, 6);
            if (args.size() == 2)
               return QVariant(QPoint(args[0].toInt(), args[1].toInt()));
         } else if (s == QLatin1String("@Invalid()")) {
            return QVariant();
         }

      }
      if (s.startsWith(QLatin1String("@@")))
         return QVariant(s.mid(1));
   }

   return QVariant(s);
}

/**
 * This function is copied from Qt src/corelib/io/qsettings.cpp
 */
QStringList XmlSettings::splitArgs(const QString &s, int idx)
{
   int l = s.length();
   Q_ASSERT(l > 0);
   Q_ASSERT(s.at(idx) == QLatin1Char('('));
   Q_ASSERT(s.at(l - 1) == QLatin1Char(')'));

   QStringList result;
   QString item;

   for (++idx; idx < l; ++idx) {
      QChar c = s.at(idx);
      if (c == QLatin1Char(')')) {
         Q_ASSERT(idx == l - 1);
         result.append(item);
      } else if (c == QLatin1Char(' ')) {
         result.append(item);
         item.clear();
      } else {
         item.append(c);
      }
   }

   return result;
}



/* protected    */

/* public       */


/******************************************************************************************
 * METHODS
 *****************************************************************************************/

/* private      */

/* protected    */

/* public       */


QVariant XmlSettings::value( const QString & key, const QVariant & defaultValue )
{
   if ( !settings().contains( key ) ){
      settings().setValue( key, defaultValue );
   }
   return settings().value( key );
}
void XmlSettings::setValue ( const QString & key, const QVariant & value )
{
   settings().setValue( key, value );
}




