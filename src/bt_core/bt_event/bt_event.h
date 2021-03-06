/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_EVENT_H
#define _BT_EVENT_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include <memory>



namespace BTCore {
    class EventVisitor;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class Event;
}

/**
 * Class that represents abstract event. See subclasses for specific event
 * types.
 */
class BTCore::Event : public std::enable_shared_from_this<BTCore::Event>
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    explicit Event(/*TODO: time*/);
    virtual ~Event();


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

    /**
     * Return human-readable string representation of the event
     */
    virtual const QString toString() const = 0;

    /**
     * Accept visitor (google "visitor pattern")
     */
    virtual void accept(EventVisitor &visitor) = 0;

    /**
     * Returns shared pointer to this instance of `Event`
     */
    std::shared_ptr<Event> getSharedPtr();


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_EVENT_H
