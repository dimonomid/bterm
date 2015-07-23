/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTIODEV_DBG_H
#define _HTIODEV_DBG_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/


#include <cstdint>
#include <vector>

#include <QTimer>

#include "htiodev.h"

using namespace std;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

class HTIODevDbg : public HTIODev
{
   Q_OBJECT
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT
    ***************************************************************************/
public:
   explicit HTIODevDbg();
   virtual ~HTIODevDbg();

   HTIODevDbg(const HTIODevDbg &other) = delete;
   HTIODevDbg(HTIODevDbg &&other) = delete;

   HTIODevDbg &operator=(const HTIODevDbg &other) = delete;
   HTIODevDbg &operator=(HTIODevDbg &&other) = delete;


   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:
   QTimer timer;
   vector<uint8_t> cur_data;

   int stage;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:

   vector<uint8_t> read() override;
   void write(const vector<uint8_t> &data) override;


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/
signals:
   //NOTE: we should NOT define signals in subclasses,
   //      since if we do, then function pointer-based
   //      connect() syntax will not generate any errors,
   //      but it will just not work silently.
   //
   //void readyRead(int bytes_available);

private slots:
   void nextMsgGenerate();


   /****************************************************************************
    * OPERATORS
    ***************************************************************************/

};


#endif // _HTIODEV_DBG_H
