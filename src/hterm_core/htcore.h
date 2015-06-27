/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTCORE_H
#define _HTCORE_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <memory>

#include <QObject>


#include "htdatasrc.h"
#include "htcodec.h"


class HTEventDataRaw;
class HTEventDataMsg;
class HTDataMsg;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

class HTCore : public QObject
{
   Q_OBJECT;

   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit HTCore(
         const std::shared_ptr<HTCodec> &p_codec,
         const std::shared_ptr<HTDataSrc> &p_data_src
         );

   virtual ~HTCore();

   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

   std::shared_ptr<HTCodec> p_codec;
   std::shared_ptr<HTDataSrc> p_data_src;


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
   void eventDataRaw(const std::shared_ptr<HTEventDataRaw> &p_event);
   void eventDataMsg(const std::shared_ptr<HTEventDataMsg> &p_event);

private slots:
   void onDataSrcReadyRead(int bytes_available);
   void onMessageDecoded(const HTDataMsg &msg);


};


#endif // _HTCORE_H
