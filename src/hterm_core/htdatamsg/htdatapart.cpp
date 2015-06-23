/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htdatapart.h"

#include <initializer_list>
#include <vector>


using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HTDataPart::HTDataPart(HTDataPart::Type type, const vector<uint8_t> &data)
{
   this->type = type;
   this->data = data;
}

HTDataPart::HTDataPart(HTDataPart::Type type, vector<uint8_t> &&data)
{
   this->type = type;
   this->data = data;
}

HTDataPart::HTDataPart(HTDataPart::Type type, const std::initializer_list<uint8_t> &data)
{
   this->type = type;
   this->data = std::vector<uint8_t>{data};
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

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


