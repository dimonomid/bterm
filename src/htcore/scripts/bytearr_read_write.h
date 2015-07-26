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

   void setFillByte(unsigned int fill_byte);

   void putU08(unsigned int index, long val);
   void putU16(unsigned int index, long val, int end = LITTLE_END);
   void putU32(unsigned int index, long val, int end = LITTLE_END);

   void putS08(unsigned int index, long val);
   void putS16(unsigned int index, long val, int end = LITTLE_END);
   void putS32(unsigned int index, long val, int end = LITTLE_END);



private:

   void ensureSize(size_t size_needed);


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/

};


#endif // _BYTEARR_READ_WRITE_H
