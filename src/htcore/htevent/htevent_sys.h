/******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HTEVENT_SYS_H
#define _HTEVENT_SYS_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htevent.h"



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class EventSys;
}

/**
 * Event that represents some system event, such as debug events (data rx/tx),
 * issues during project opening, etc.
 */
class HTCore::EventSys : public Event
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


#endif // _HTEVENT_SYS_H
