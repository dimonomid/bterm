/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htdatasrc_dbg.h"

#include <vector>
#include <stdexcept>
#include <tuple>


/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HTDataSrcDbg::HTDataSrcDbg() :
   timer(this),
   cur_data(),
   stage(0)
{
   connect(&timer, SIGNAL(timeout()), this, SLOT(nextMsgGenerate()));
   timer.start(200);
}

HTDataSrcDbg::~HTDataSrcDbg()
{
   disconnect(&timer, SIGNAL(timeout()), this, SLOT(nextMsgGenerate()));
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

vector<uint8_t> HTDataSrcDbg::read()
{
   vector<uint8_t> ret = std::move(cur_data);
   cur_data = vector<uint8_t>{};
   return ret;
}

void HTDataSrcDbg::write(const vector<uint8_t> &data)
{
   std::ignore = data;
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void HTDataSrcDbg::nextMsgGenerate()
{
   qDebug("here I am");

   vector<uint8_t> new_data;

   switch (stage){
      case 0:
         new_data = {0x31, 0x80};
         break;
      case 1:
         new_data = {0x03, 0x02, 0x01};
         break;
      case 2:
         new_data = {0x04, 0x05, 0x06, 0x95,   0x07};
         break;
   }

   stage++;
   if (stage > 2){
      stage = 0;
   }

   cur_data.insert(
         cur_data.end(),
         new_data.cbegin(), new_data.cend()
         );

   emit(readyRead(cur_data.size()));
}

/* protected    */

/* public       */


