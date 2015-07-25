/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bytearr_read_write.h"

#include <algorithm>


using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ByteArrReadWrite::ByteArrReadWrite() :
   ByteArrRead(std::vector<uint8_t>()),
   fill_byte(0x00)
{
}

ByteArrReadWrite::ByteArrReadWrite(const std::vector<uint8_t> &data) :
   ByteArrRead(data),
   fill_byte(0x00)
{
}

ByteArrReadWrite::ByteArrReadWrite(size_t size, uint8_t fill_byte) :
   ByteArrRead(std::vector<uint8_t>(size, fill_byte)),
   fill_byte(fill_byte)
{
}



/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

void ByteArrReadWrite::ensureSize(size_t size_needed)
{
   if (p_data->size() < size_needed){
      size_t size_before = p_data->size();
      p_data->resize(size_needed);
      std::fill(
            p_data->begin() + size_before,
            p_data->begin() + size_needed,
            fill_byte
            );
   }
}

/* protected    */

/* public       */

void ByteArrReadWrite::setFillByte(unsigned int fill_byte)
{
   this->fill_byte = fill_byte;
}


void ByteArrReadWrite::putU08(unsigned int index, unsigned int val)
{
   ensureSize(index + sizeof(uint8_t));

   (*p_data)[index] = val;
}




/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


