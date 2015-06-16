/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htdatamsg.h"



#include <vector>

using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HTDataMsg::HTDataMsg() :
   data_parts(vector<HTDataPart>())
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

void HTDataMsg::addData(HTDataPart::Type type, unsigned char byte)
{
   if (this->data_parts.size() > 0 && type == this->data_parts.back().type){
      //-- type of new data is the same as previously added data, so, just
      //   append it to last data part

      this->data_parts.back().data.push_back(byte);
   } else {
      //-- type of new data differs from that of previously added data
      //   (or we haven't any data yet), so, add new data part

      auto data = vector<unsigned char>();
      data.push_back(byte);

      this->data_parts.push_back(
            HTDataPart(type, data)
            );
   }
}

void HTDataMsg::addData(HTDataPart::Type type, const vector<unsigned char> &data)
{
   if (this->data_parts.size() > 0 && type == this->data_parts.back().type){
      //-- type of new data is the same as previously added data, so, just
      //   append it to last data part

      this->data_parts.back().data.insert(
            this->data_parts.back().data.end(),
            data.begin(),
            data.end()
            );
   } else {
      //-- type of new data differs from that of previously added data
      //   (or we haven't any data yet), so, add new data part

      this->data_parts.push_back(
            HTDataPart(type, data)
            );
   }

}

void HTDataMsg::clear()
{
   this->data_parts.clear();
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


