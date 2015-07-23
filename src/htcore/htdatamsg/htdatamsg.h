/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTDATAMSG_H
#define _HTDATAMSG_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>

#include <vector>
#include <string>

#include "htdatapart.h"



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
   class DataMsg;
}



class HTCore::DataMsg
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit DataMsg();


   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

   std::vector<DataPart> data_parts;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/

public:
   void addData(DataPart::DataType data_type, const std::vector<uint8_t> &data);
   void addData(DataPart::DataType data_type, uint8_t byte);
   void addData(DataPart data_part);

   void clear();

   std::vector<uint8_t> getUserData() const;
   std::vector<uint8_t> getRawData() const;

   std::vector<DataPart> getDataParts() const;

   std::string toString() const;

   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/


   /*******************************************************************************
    * OPERATORS
    ******************************************************************************/

public:
   inline bool operator==(const DataMsg &other) const {
      return (this->data_parts == other.data_parts);
   }
};


#endif // _HTDATAMSG_H
