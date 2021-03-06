/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_EVENT_VISITOR_H
#define _BT_EVENT_VISITOR_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_event.h"




namespace BTCore {
    class EventDataRaw;
    class EventDataMsg;
    class EventSys;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class EventVisitor;
}

/**
 * Abstract visitor for `#BTCore::Event`
 *
 * (if you're unfamiliar with visitor pattern, read about it somewhere; for
 * example, on Wikipedia: https://en.wikipedia.org/wiki/Visitor_pattern )
 */
class BTCore::EventVisitor : public QObject
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual void visit(EventDataRaw &) = 0;
    virtual void visit(EventDataMsg &) = 0;
    virtual void visit(EventSys &) = 0;




    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_EVENT_VISITOR_H
