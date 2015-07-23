/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bytearr.h"


using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ByteArr::ByteArr() :
   p_data(new std::vector<uint8_t>())
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

/* protected    */

/* public       */

unsigned int ByteArr::getU08(unsigned int index)
{
   unsigned int ret = 0x100;
   if (p_data->size() > index){
      ret = (*p_data)[index];
   }

   return ret;
}

void ByteArr::putU08(unsigned int index, unsigned int val)
{
   if (p_data->size() <= index){
      p_data->resize(index + 1);
   }

   (*p_data)[index] = val;
}


std::shared_ptr<const std::vector<uint8_t>> ByteArr::getData() const
{
   return p_data;
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


