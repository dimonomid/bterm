/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTEVENT_VISITOR_HANDLE_H
#define _HTEVENT_VISITOR_HANDLE_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include "htevent_visitor.h"


class Appl;

namespace HTCore {
    class DataMsg;
    class EventDataRaw;
    class EventDataMsg;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/


class EventVisitor_Handle : public HTCore::EventVisitor
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    EventVisitor_Handle(Appl &appl);

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    Appl &appl;

    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual void visit(HTCore::EventDataRaw &htevent_data_raw) override;
    virtual void visit(HTCore::EventDataMsg &htevent_data_msg) override;
    virtual void visit(HTCore::EventSys &htevent_data_msg) override;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:

    void newDataRaw(const std::vector<uint8_t> &data);
    void newDataMsg(const HTCore::DataMsg &msg);

};


#endif // _HTEVENT_VISITOR_HANDLE_H
