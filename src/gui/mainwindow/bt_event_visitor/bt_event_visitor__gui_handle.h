/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _BT_EVENT_VISITOR__GUI_HANDLE_H
#define _BT_EVENT_VISITOR__GUI_HANDLE_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include "bt_event_visitor.h"


class MainWindow;

namespace BTCore {
    class EventDataRaw;
    class EventDataMsg;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/


/**
 * Concrete visitor for `#BTCore::Event`, implements `guiHandle()` method: it
 * reflects the event in the GUI. Usually this means adding new message to the
 * log.
 */
class EventVisitor_GuiHandle : public BTCore::EventVisitor
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    EventVisitor_GuiHandle(MainWindow &mainwindow);

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    MainWindow &mainwindow;

    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual void visit(BTCore::EventDataRaw &bt_event_data_raw) override;
    virtual void visit(BTCore::EventDataMsg &bt_event_data_msg) override;
    virtual void visit(BTCore::EventSys &bt_event_data_msg) override;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_EVENT_VISITOR__GUI_HANDLE_H
