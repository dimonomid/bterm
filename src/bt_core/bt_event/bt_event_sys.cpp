/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_event_sys.h"
#include "bt_event_visitor.h"


using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

EventSys::EventSys(MsgLevel level, QString text) :
    level(level),
    text(text)
{

}

EventSys::~EventSys()
{
}



/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */

QString EventSys::levelToString(MsgLevel level)
{
    QString ret = "unknown";

    switch (level){
        case MsgLevel::DEBUG:
            ret = "DEBUG";
            break;
        case MsgLevel::INFO:
            ret = "INFO";
            break;
        case MsgLevel::WARNING:
            ret = "WARNING";
            break;
        case MsgLevel::ERROR:
            ret = "ERROR";
            break;
    }

    return ret;
}

MsgLevel EventSys::levelFromString(QString level_str)
{
    MsgLevel level = MsgLevel::INFO;

    if (level_str == "DEBUG"){
        level = MsgLevel::DEBUG;
    } else if (level_str == "INFO"){
        level = MsgLevel::INFO;
    } else if (level_str == "WARNING"){
        level = MsgLevel::WARNING;
    } else if (level_str == "ERROR"){
        level = MsgLevel::ERROR;
    }

    return level;
}


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */

const QString EventSys::toString() const
{
    return text;
}

MsgLevel EventSys::getLevel() const
{
    return level;
}

void EventSys::accept(EventVisitor &visitor)
{
    visitor.visit(*this);
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


