/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htevent_sys.h"
#include "htevent_visitor.h"


using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

EventSys::EventSys(Level level, QString text) :
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

QString EventSys::levelToString(Level level)
{
    QString ret = "unknown";

    switch (level){
        case Level::DEBUG:
            ret = "DEBUG";
            break;
        case Level::INFO:
            ret = "INFO";
            break;
        case Level::WARNING:
            ret = "WARNING";
            break;
        case Level::ERROR:
            ret = "ERROR";
            break;
    }

    return ret;
}

EventSys::Level EventSys::levelFromString(QString level_str)
{
    Level level = Level::INFO;

    if (level_str == "DEBUG"){
        level = Level::DEBUG;
    } else if (level_str == "INFO"){
        level = Level::INFO;
    } else if (level_str == "WARNING"){
        level = Level::WARNING;
    } else if (level_str == "ERROR"){
        level = Level::ERROR;
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

EventSys::Level EventSys::getLevel() const
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


