/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <vector>
#include <cstdint>

#include "htevent_data_msg.h"
#include "htevent_visitor.h"



using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

EventDataMsg::EventDataMsg(
        const DataMsg &msg,
        Direction dir,
        std::shared_ptr<ReqHandler> p_handler
        )
    :
    msg(msg),
    dir(dir),
    p_handler(p_handler)
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

const DataMsg EventDataMsg::getMsg() const
{
    return msg;
}

EventDataMsg::Direction EventDataMsg::getDir() const
{
    return dir;
}

std::shared_ptr<ReqHandler> EventDataMsg::getHandler() const
{
    return p_handler;
}


void EventDataMsg::accept(EventVisitor &visitor)
{
    visitor.accept(*this);
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


