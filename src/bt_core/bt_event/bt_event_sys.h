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
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
    };

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    explicit EventSys(Level level, QString text);
    virtual ~EventSys();


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    Level level;
    QString text;



    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/
public:
    static QString levelToString(Level level);
    static Level levelFromString(QString level_str);


    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual const QString toString() const override;
    Level getLevel() const;
    virtual void accept(EventVisitor &visitor) override;



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_EVENT_SYS_H
