/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include "htevent_visitor__gui_handle.h"

#include "htevent_data_raw.h"
#include "htevent_data_msg.h"
#include "htevent_sys.h"

#include "mainwindow.h"
#include "qplaintextedit_my.h"
#include "my_util.h"
#include "htreqhandler.h"


using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

EventVisitor_GuiHandle::EventVisitor_GuiHandle(MainWindow &mainwindow) :
    mainwindow(mainwindow)
{
}



/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */

void EventVisitor_GuiHandle::visit(EventDataRaw &htevent_data_raw)
{
    QString text = MyUtil::byteArrayToHex(htevent_data_raw.getData()) + "<br>";

    mainwindow.p_raw_data_pte->appendHtmlNoNL(text, true);
}

void EventVisitor_GuiHandle::visit(EventDataMsg &htevent_data_msg)
{
    QString dir_text = "";
    QString handler_text = "";
    QString color = "black";

    switch (htevent_data_msg.getDir()){
        case EventDataMsg::Direction::TX:
            dir_text = "Tx";
            color = "blue";
            handler_text = " (" + htevent_data_msg.getHandler()->getTitle() + ")";
            break;
        case EventDataMsg::Direction::RX:
            dir_text = "Rx";
            break;
        default:
            //-- should never be here
            break;
    }

    QString text = "<font color='" + color + "'><b>msg " + dir_text + ":</b>" + handler_text + " " + MyUtil::byteArrayToHex(
            *htevent_data_msg.getMsg().getUserData()
            ) + "</font><br>";

    mainwindow.p_log_pte->appendHtmlNoNL(text, true);
}

void EventVisitor_GuiHandle::visit(EventSys &htevent_sys)
{
    if (true/*event_sys.getLevel() >= mainwindow.sys_msg_level*/){
        QString html {};

        switch (htevent_sys.getLevel()){
            case EventSys::Level::DEBUG:
                html = "<font color='green'>" + htevent_sys.toString() + "</font>";
                break;
            case EventSys::Level::INFO:
                html = "<font color='blue'>" + htevent_sys.toString() + "</font>";
                break;
            case EventSys::Level::WARNING:
                html = "<font color='brown'>" + htevent_sys.toString() + "</font>";
                break;
            case EventSys::Level::ERROR:
                html = "<font color='red'>" + htevent_sys.toString() + "</font>";
                break;
        }

        mainwindow.p_log_pte->appendHtmlNoNL("* " + html + "<br>", true);
    }
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


