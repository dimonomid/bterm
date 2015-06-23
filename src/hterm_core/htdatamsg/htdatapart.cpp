/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htdatapart.h"

#include <vector>
#include <stdexcept>


using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HTDataPart::HTDataPart()
{
}

HTDataPart::HTDataPart(HTDataPart::DataType data_type, const vector<uint8_t> &data) :
   service_data(data_type == DataType::SERVICE ? data : std::vector<uint8_t>{}),
   user_data   (data_type == DataType::USER    ? data : std::vector<uint8_t>{})
{
}

HTDataPart::HTDataPart(HTDataPart::DataType data_type, vector<uint8_t> &&data) :
   service_data(data_type == DataType::SERVICE ? data : std::vector<uint8_t>{}),
   user_data   (data_type == DataType::USER    ? data : std::vector<uint8_t>{})
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

void HTDataPart::addData(DataType data_type, const vector<uint8_t> &data)
{
   switch (data_type){
      case HTDataPart::DataType::SERVICE:
         this->service_data.insert(
               this->service_data.end(),
               data.cbegin(), data.cend()
               );
         break;
      case HTDataPart::DataType::USER:
         this->user_data.insert(
               this->user_data.end(),
               data.cbegin(), data.cend()
               );
         break;
   }
}

void HTDataPart::addData(DataType data_type, uint8_t byte)
{
   switch (data_type){
      case HTDataPart::DataType::SERVICE:
         this->service_data.push_back(byte);
         break;
      case HTDataPart::DataType::USER:
         this->user_data.push_back(byte);
         break;
   }
}



vector<uint8_t> HTDataPart::getData(HTDataPart::DataType data_type) const
{
   vector<uint8_t> ret;

   switch (data_type){
      case HTDataPart::DataType::SERVICE:
         ret = this->service_data;
         break;
      case HTDataPart::DataType::USER:
         ret = this->user_data;
         break;
   }

   return ret;
}


HTDataPart::PartType HTDataPart::getType() const
{
   HTDataPart::PartType ret;

   if (user_data.size() != 0 && service_data.size() == 0){
      ret = HTDataPart::PartType::USER;
   } else if (user_data.size() == 0 && service_data.size() != 0){
      ret = HTDataPart::PartType::SERVICE;
   } else if (user_data.size() != 0 && service_data.size() != 0){
      ret = HTDataPart::PartType::COMBINED;
   } else {
      ret = HTDataPart::PartType::EMPTY;
   }

   return ret;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


