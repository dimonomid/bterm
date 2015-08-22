/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include "htevent_visitor__appl_handle.h"

#include "htevent_data_raw.h"
#include "htevent_data_msg.h"

#include "appl.h"


using namespace HTCore;

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

void EventVisitor_ApplHandle::visit(EventDataRaw &htevent_data_raw)
{
    appl.p_events_data_raw->addEvent(
            std::dynamic_pointer_cast<EventDataRaw>(
                htevent_data_raw.getSharedPtr()
                )
            );
}

void EventVisitor_ApplHandle::visit(EventDataMsg &htevent_data_msg)
{
    appl.p_events_data_msg->addEvent(
            std::dynamic_pointer_cast<EventDataMsg>(
                htevent_data_msg.getSharedPtr()
                )
            );
}

void EventVisitor_ApplHandle::visit(EventSys &htevent_sys)
{
    std::ignore = htevent_sys;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


