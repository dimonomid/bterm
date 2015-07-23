/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTPROJECT_H
#define _HTPROJECT_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <memory>

#include <QObject>


#include "htiodev.h"
#include "htcodec.h"



namespace HTCore {
   class EventDataRaw;
   class EventDataMsg;
   class DataMsg;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
   class Project;
}


class HTCore::Project : public QObject
{
   Q_OBJECT;

   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit Project(
         std::shared_ptr<Codec> p_codec,
         std::shared_ptr<HTIODev> p_io_dev
         );

   virtual ~Project();

   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

   std::shared_ptr<Codec> p_codec;
   std::shared_ptr<HTIODev> p_io_dev;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/

   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/
signals:
   void eventDataRaw(std::shared_ptr<EventDataRaw> p_event);
   void eventDataMsg(std::shared_ptr<EventDataMsg> p_event);

private slots:
   void onDataSrcReadyRead(int bytes_available);
   void onMessageDecoded(const DataMsg &msg);


};


#endif // _HTPROJECT_H
