/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTDATAPART_H
#define _HTDATAPART_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>

#include <vector>



using namespace std;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

class HTDataPart
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/
public:
   enum class DataType { SERVICE, USER };
   enum class PartType { SERVICE, USER, COMBINED, EMPTY };

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit HTDataPart();
   explicit HTDataPart(DataType data_type, const vector<uint8_t> &data);
   explicit HTDataPart(DataType data_type, vector<uint8_t> &&data);

   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:
   vector<uint8_t> service_data;
   vector<uint8_t> user_data;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:

   void addData(DataType data_type, const vector<uint8_t> &data);
   void addData(DataType data_type, uint8_t byte);

   vector<uint8_t> getData(DataType data_type) const;
   PartType getType() const;

   /**
    * Returns whether data of given type could be added to the data part
    * without breaking part's homogeneity.
    *
    * The part is homogeneous if it is either empty or contains
    * data of only single type (SERVICE or USER), but not both.
    */
   bool canDataBeAddedHomogeneously(DataType data_type) const;


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/


   /*******************************************************************************
    * OPERATORS
    ******************************************************************************/

public:
   inline bool operator==(const HTDataPart &other) const {
      return (this->user_data == other.user_data && this->service_data == other.service_data);
   }
};

/**
 * Treat SERVICE and USER to be equal in both DataType and PartType, all other variants
 * are non-equal
 */
#if 0
inline bool operator==(const HTDataPart::DataType &data_type, const HTDataPart::PartType &part_type){
   return (
         (data_type == HTDataPart::DataType::SERVICE && part_type == HTDataPart::PartType::SERVICE)
         ||
         (data_type == HTDataPart::DataType::USER && part_type == HTDataPart::PartType::USER)
         );
}

inline bool operator==(const HTDataPart::PartType &part_type, const HTDataPart::DataType &data_type){
   return (data_type == part_type);
}
#endif


#endif // _HTDATAPART_H
