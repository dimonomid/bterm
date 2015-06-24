/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include "htevent_visitor_handle.h"

#include "htevent_data_raw.h"
#include "htevent_data_msg.h"


/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HTEventVisitor_Handle::HTEventVisitor_Handle(Appl &appl) : 
   appl(appl)
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

void HTEventVisitor_Handle::accept(HTEventDataRaw &htevent_data_raw)
{
   const std::vector<uint8_t> data = htevent_data_raw.getData();
   qDebug("handle data raw: ");
   for (auto byte : data){
      qDebug("0x%2.x", byte);
   }
}

void HTEventVisitor_Handle::accept(HTEventDataMsg &htevent_data_msg)
{
   qDebug(("handle data msg: " + htevent_data_msg.getMsg().toString()).c_str());
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


