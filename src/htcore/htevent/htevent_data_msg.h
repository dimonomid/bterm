/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTEVENT_DATA_MSG_H
#define _HTEVENT_DATA_MSG_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include "htevent.h"
#include "htdatamsg.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class EventDataMsg;
    class ReqHandler;
}


class HTCore::EventDataMsg : public HTCore::Event
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

public:

    enum class Direction {
        RX,
        TX,
    };


    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    /**
     * @param p_handler
     *      Used if only dir == Direction::TX. Represents a handler that
     *      generated a message.
     */
    EventDataMsg(
            const DataMsg &msg,
            Direction dir,
            std::shared_ptr<HTCore::ReqHandler> p_handler = nullptr
            );


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    DataMsg msg;
    Direction dir;
    std::shared_ptr<ReqHandler> p_handler;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    const DataMsg getMsg() const;
    Direction getDir() const;
    std::shared_ptr<ReqHandler> getHandler() const;

    virtual const QString toString() const override;
    virtual void accept(EventVisitor &visitor) override;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _HTEVENT_DATA_MSG_H
