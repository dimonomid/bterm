/*******************************************************************************
 *   Description:   Accumulator of HTEvent-s
 *
 ******************************************************************************/

#ifndef _TPL_H
#define _TPL_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <deque>
#include <vector>
#include <memory>

#include <QObject>



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

template<typename T>
class HTEventsAcc
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:

   explicit HTEventsAcc(size_t max_events_cnt) :
      max_events_cnt(max_events_cnt),
      events(),
      last_event_num(0)
   {

   }


   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

   //-- maximum number of items that deque could contain
   size_t max_events_cnt;

   //-- actual collection of events
   std::deque<std::shared_ptr<T>> events;

   //-- incremented at every new event. never decremented.
   //   must always be >= events.size()
   unsigned long last_event_num;




   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:
   std::vector<std::shared_ptr<T>> getEvents(
         unsigned long start_event_num,
         unsigned long *p_last_event_num
         )
   {
      std::vector<std::shared_ptr<T>> new_events {};

      if (start_event_num < this->last_event_num){
         //-- get number of the event at `this->events[0]`.
         //   Note: the condition (last_event_num >= events.size()) is always true.
         unsigned long idx0_event_num = this->last_event_num - this->events.size();

         //-- get start iterator
         typename std::deque<std::shared_ptr<T>>::iterator iter = events.cbegin();
         if (start_event_num > idx0_event_num){
            iter += (start_event_num - idx0_event_num);
         }

         //-- copy items to the vector that will be returned
         new_events.insert(
               new_events.begin(),
               iter, events.cend()
               );
      }

      //-- if user asked to provide last event number, write it
      //   at user's location
      if (p_last_event_num != nullptr){
         *p_last_event_num = this->last_event_num;
      }

      return new_events;
   }


   void addEvent(std::shared_ptr<T> p_event)
   {
      events.push_back(p_event);
      last_event_num++;

      //-- if we have too many events, delete oldest
      if (max_events_cnt > 0 && events.size() > max_events_cnt){
         int cnt_to_delete = events.size() - max_events_cnt;
         while (cnt_to_delete-- > 0){
            events.pop_front();
         }
      }
   }


};


#endif // _TPL_H
