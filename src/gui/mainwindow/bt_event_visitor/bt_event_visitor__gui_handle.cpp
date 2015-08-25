/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include "bt_event_visitor__gui_handle.h"

#include "bt_event_data_raw.h"
#include "bt_event_data_msg.h"
#include "bt_event_sys.h"

#include "mainwindow.h"
#include "qplaintextedit_my.h"
#include "my_util.h"
#include "bt_reqhandler.h"


using namespace BTCore;

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

void EventVisitor_GuiHandle::visit(EventDataRaw &bt_event_data_raw)
{
    QString text = MyUtil::byteArrayToHex(bt_event_data_raw.getData()) + "<br>";

    mainwindow.p_raw_data_pte->appendHtmlNoNL(text, true);
}

void EventVisitor_GuiHandle::visit(EventDataMsg &bt_event_data_msg)
{
    QString dir_text = "";
    QString handler_text = "";
    QString color = "black";

    switch (bt_event_data_msg.getDir()){
        case EventDataMsg::Direction::TX:
            dir_text = "Tx";
            color = "blue";
            handler_text = " (" + bt_event_data_msg.getDescr() + ")";
            break;
        case EventDataMsg::Direction::RX:
            dir_text = "Rx";
            break;
        default:
            //-- should never be here
            break;
    }

    QString text = "<font color='" + color + "'><b>msg " + dir_text + ":</b>" + handler_text + " " + MyUtil::byteArrayToHex(
            *bt_event_data_msg.getMsg().getUserData()
            ) + "</font><br>";

    mainwindow.p_log_pte->appendHtmlNoNL(text, true);
}

void EventVisitor_GuiHandle::visit(EventSys &bt_event_sys)
{
    if (true/*event_sys.getLevel() >= mainwindow.sys_msg_level*/){
        QString bt_ml {};

        switch (bt_event_sys.getLevel()){
            case MsgLevel::DEBUG:
                bt_ml = "<font color='green'>" + bt_event_sys.toString() + "</font>";
                break;
            case MsgLevel::INFO:
                bt_ml = "<font color='blue'>" + bt_event_sys.toString() + "</font>";
                break;
            case MsgLevel::WARNING:
                bt_ml = "<font color='brown'>" + bt_event_sys.toString() + "</font>";
                break;
            case MsgLevel::ERROR:
                bt_ml = "<font color='red'>" + bt_event_sys.toString() + "</font>";
                break;
        }

        mainwindow.p_log_pte->appendHtmlNoNL("* " + bt_ml + "<br>", true);
    }
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


