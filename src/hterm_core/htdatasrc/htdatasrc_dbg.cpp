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
   timer(this)
{
   connect(&timer, SIGNAL(timeout()), this, SLOT(nextMsgGenerate()));
   timer.start(1000);
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
}

/* protected    */

/* public       */


