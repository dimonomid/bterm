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

#include <initializer_list>
#include <vector>



using namespace std;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

struct HTDataPart
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/
public:
   enum class Type { SERVICE, USER };

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit HTDataPart(Type type, const vector<uint8_t> &data);
   explicit HTDataPart(Type type, vector<uint8_t> &&data);
   explicit HTDataPart(Type type, const std::initializer_list<uint8_t> &data);

   /****************************************************************************
    * PUBLIC DATA
    ***************************************************************************/
   Type type;
   vector<uint8_t> data;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/

   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/


   /*******************************************************************************
    * OPERATORS
    ******************************************************************************/

public:
   inline bool operator==(const HTDataPart &other) const {
      return (this->data == other.data);
   }
};


#endif // _HTDATAPART_H
