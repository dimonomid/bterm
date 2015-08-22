/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _BT_EVENT_DATA_MSG_H
#define _BT_EVENT_DATA_MSG_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include "bt_event.h"
#include "bt_datamsg.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class EventDataMsg;
    class ReqHandler;
}


class BTCore::EventDataMsg : public BTCore::Event
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

public:

    /**
     * Direction of the message: Rx or Tx.
     */
    enum class Direction {
        RX,
        TX,
    };


    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    /**
     * @param msg
     *      Message that this event is about
     * @param dir
     *      Direction of the message: Rx or Tx. See `#Direction`.
     * @param p_handler
     *      Used if only dir == Direction::TX. Represents a handler that
     *      generated a message.
     */
    EventDataMsg(
            const DataMsg &msg,
            Direction dir,
            std::shared_ptr<BTCore::ReqHandler> p_handler = nullptr
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


#endif // _BT_EVENT_DATA_MSG_H
