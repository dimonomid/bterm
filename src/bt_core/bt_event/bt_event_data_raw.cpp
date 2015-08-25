/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <vector>
#include <cstdint>

#include "bt_event_data_raw.h"
#include "bt_event_visitor.h"



using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

EventDataRaw::EventDataRaw(const std::vector<uint8_t> &data) :
    data(data)
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

const std::vector<uint8_t> EventDataRaw::getData() const
{
    return data;
}

const QString EventDataRaw::toString() const
{
    return "EventDataRaw";
}

void EventDataRaw::accept(EventVisitor &visitor)
{
    visitor.visit(*this);
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


