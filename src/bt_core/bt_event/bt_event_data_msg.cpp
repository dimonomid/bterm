/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <vector>
#include <cstdint>

#include "bt_event_data_msg.h"
#include "bt_event_visitor.h"



using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

EventDataMsg::EventDataMsg(
        const DataMsg &msg,
        Direction dir,
        QString descr
        )
    :
    msg(msg),
    dir(dir),
    descr(descr)
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

QString EventDataMsg::getDescr() const
{
    return descr;
}


const QString EventDataMsg::toString() const
{
    return "EventDataMsg";
}

void EventDataMsg::accept(EventVisitor &visitor)
{
    visitor.visit(*this);
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


