/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _HTEVENT_H
#define _HTEVENT_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>




class HTEventVisitor;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

class HTEvent
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit HTEvent(/*TODO: time*/);
   virtual ~HTEvent();


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

   virtual void accept(HTEventVisitor &visitor) = 0;



   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/

};


#endif // _HTEVENT_H
