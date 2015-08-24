/******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_EVENT_SYS_H
#define _BT_EVENT_SYS_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_event.h"
#include "bt_core.h"



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class EventSys;
}

/**
 * Event that represents some system event, such as debug events (data rx/tx),
 * issues during project opening, etc.
 */
class BTCore::EventSys : public Event
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

public:

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    explicit EventSys(BTCore::MsgLevel level, QString text);
    virtual ~EventSys();


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    BTCore::MsgLevel level;
    QString text;



    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/
public:
    static QString levelToString(BTCore::MsgLevel level);
    static MsgLevel levelFromString(QString level_str);


    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual const QString toString() const override;
    BTCore::MsgLevel getLevel() const;
    virtual void accept(EventVisitor &visitor) override;



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_EVENT_SYS_H
