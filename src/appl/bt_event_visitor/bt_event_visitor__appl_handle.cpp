/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include "bt_event_visitor__appl_handle.h"

#include "bt_event_data_raw.h"
#include "bt_event_data_msg.h"

#include "appl.h"


using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

EventVisitor_ApplHandle::EventVisitor_ApplHandle(Appl &appl) :
    appl(appl)
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

void EventVisitor_ApplHandle::visit(EventDataRaw &bt_event_data_raw)
{
    //-- add event to accumulator
    appl.p_events_data_raw->addEvent(
            std::dynamic_pointer_cast<EventDataRaw>(
                bt_event_data_raw.getSharedPtr()
                )
            );
}

void EventVisitor_ApplHandle::visit(EventDataMsg &bt_event_data_msg)
{
    //-- add event to accumulator
    appl.p_events_data_msg->addEvent(
            std::dynamic_pointer_cast<EventDataMsg>(
                bt_event_data_msg.getSharedPtr()
                )
            );
}

void EventVisitor_ApplHandle::visit(EventSys &bt_event_sys)
{
    std::ignore = bt_event_sys;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


