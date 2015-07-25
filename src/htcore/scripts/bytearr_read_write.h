/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BYTEARR_READ_WRITE_H
#define _BYTEARR_READ_WRITE_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include <memory>
#include <vector>
#include <cstdint>

#include "bytearr_read.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
   class ByteArrReadWrite;
}

/*
 * TODO: implement the fill byte
 *       implement unit tests
 */

/**
 * TODO
 */
class HTCore::ByteArrReadWrite : public HTCore::ByteArrRead
{
   Q_OBJECT
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit ByteArrReadWrite();
   explicit ByteArrReadWrite(const std::vector<uint8_t> &data);
   explicit ByteArrReadWrite(size_t size, uint8_t fill_byte);


   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

   uint8_t fill_byte;



   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/


public slots:

   void putU08(unsigned int index, unsigned int val);
   void setFillByte(unsigned int fill_byte);


private:

   void ensureSize(size_t size_needed);


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/

};


#endif // _BYTEARR_READ_WRITE_H
