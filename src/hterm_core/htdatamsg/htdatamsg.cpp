/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htdatamsg.h"



#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

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

std::string HTDataMsg::toString() const {

   std::stringstream ss{};
   bool empty = true;

   for (auto data_part : this->data_parts){
      for (int byte : data_part.data){
         if (!empty){
            ss << ", ";
         }

         switch (data_part.type){

            case HTDataPart::Type::SERVICE:
               ss << "*0x" << std::hex << byte << "*";
               break;

            case HTDataPart::Type::USER:
               ss << "0x" << std::hex << byte;
               break;

            default:
               std::cerr << "wrong data_part.type";
               exit(1);
               break;
         }
         empty = false;
      }
   }

   return ss.str();

   //return "data parts cnt=" + std::to_string(this->data_parts.size());
}

vector<unsigned char> HTDataMsg::getUserData() const
{
   vector<unsigned char> ret{};

   for (auto data_part : this->data_parts){
      if (data_part.type == HTDataPart::Type::USER){
         ret.insert(
               ret.end(),
               data_part.data.cbegin(), data_part.data.cend()
               );
      }
   }

   return ret;
}

vector<unsigned char> HTDataMsg::getRawData() const
{
   vector<unsigned char> ret{};

   for (auto data_part : this->data_parts){
      ret.insert(
            ret.end(),
            data_part.data.cbegin(), data_part.data.cend()
            );
   }

   return ret;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */




