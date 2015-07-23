/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <memory>



#include "appl.h"

#include "htcodec.h"
#include "htcodec_iso14230.h"

#include "htiodev.h"
#include "htiodev_dbg.h"

#include "htdatamsg.h"

//#include "htevent_data_raw.h"
//#include "htevent_data_msg.h"



//TODO: remove
#include <QScriptEngine>
#include <QScriptValue>
#include <QVariant>
#include <QDebug>
#include "bytearr.h"
#include "my_util.h"

using namespace HTCore;
using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

Appl::Appl() :
   p_codec(nullptr),
   p_io_dev(nullptr),
   p_project(nullptr),
   htevent_visitor_handle(*this),
   p_main_window(std::unique_ptr<MainWindow>(new MainWindow(*this)))
{

   p_io_dev = std::make_shared<IODevDbg>();
   p_codec = std::make_shared<Codec_ISO14230>(0x01, 0x02);

   p_project = std::unique_ptr<Project>{
      new Project{p_codec, p_io_dev}
   };

   p_events_data_raw = std::unique_ptr<EventsAcc<EventDataRaw>>{
      new EventsAcc<EventDataRaw>(1000/*TODO: settings*/)
   };

   p_events_data_msg = std::unique_ptr<EventsAcc<EventDataMsg>>{
      new EventsAcc<EventDataMsg>(1000/*TODO: settings*/)
   };



   connect(
         p_project.get(), &Project::eventDataRaw,
         this, &Appl::onNewDataRaw
         );

   connect(
         p_project.get(), &Project::eventDataMsg,
         this, &Appl::onNewDataMsg
         );



   this->p_main_window->show();

#if 1
   {
      QScriptEngine engine;
      QScriptValue result;

      ByteArr *bytearr = new ByteArr;
      QScriptValue bytearrValue = engine.newQObject(bytearr);
      engine.globalObject().setProperty("byteArr", bytearrValue);

      qDebug() << MyUtil::byteArrayToHex(*bytearr->getData());


      QScriptValue val = engine.evaluate(
            "(function(){ "
            "     byteArr.putU08(4, 0x10);"
            "     byteArr.putU08(1, 0xff);"
            " })();"
            );
      qDebug() << val.toVariant();

      qDebug() << MyUtil::byteArrayToHex(*bytearr->getData());

   }
#endif

#if 0
   {
      QScriptEngine engine;
      QScriptValue result;

      QScriptValue val = engine.newArray(3);
      val.setProperty(0, 10);
      val.setProperty(1, 11);
      val.setProperty(2, 12);

#if 1
      {
         QScriptValue myCreate = engine.evaluate(
               "(function(){ "
               "     var a = 10;"
               "     var b = 11;"
               "     var that = {};"
               "     that.getA = function(){ return a; };"
               "     that.getB = function(){ return b; };"
               "     return that;"
               " })"
               );
         engine.globalObject().setProperty("myCreate", myCreate);

         result = engine.evaluate(""
               "myCreate = null;"
               );

         engine.globalObject().setProperty("myCreate", myCreate);
         result = engine.evaluate(""
               "var test = new myCreate();"
               "test.getA();"
               );

      }
#endif

#if 0
      {
         QScriptValue myCtor = engine.evaluate(
               "(function(){ this.a = 1; this.b = 2; })"
               );
         engine.globalObject().setProperty("MyCtor", myCtor);

         result = engine.evaluate(""
               "MyCtor = null;"
               );

         engine.globalObject().setProperty("MyCtor", myCtor);
         result = engine.evaluate(""
               "var test = new MyCtor();"
               "test"
               );

      }
#endif

#if 0
      engine.globalObject().setProperty("input", val);
      //engine.pushContext();
      //result = engine.evaluate("var qwe = 123;");
      //engine.popContext();
      result = engine.evaluate(QString("")
            + "(function(){ "
            + "   print('sdf');"
            + "   var ret = [];"
            + "   ret[5] = 0xff;"
            + "   return ret;"
            //+ "   return input.map(function(n){"
            //+ "      return n * 2;"
            //+ "   });"
            + "})();"
            );
#endif

      if (engine.hasUncaughtException()){
         qDebug() << "exception: " << result.toVariant();
      } else {
         qDebug() << "the result is is:" << result.toVariant();
      }
   }
#endif
}

Appl::~Appl()
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

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

#if 0
void Appl::onEvent(const std::shared_ptr<Event> &p_event)
{
   p_event->accept(htevent_visitor_handle);
}
#endif

void Appl::onNewDataRaw(std::shared_ptr<EventDataRaw> p_event)
{
   p_events_data_raw->addEvent(p_event);

   emit eventDataRaw(p_event);
}

void Appl::onNewDataMsg(std::shared_ptr<EventDataMsg> p_event)
{
   p_events_data_msg->addEvent(p_event);

   emit eventDataMsg(p_event);
}





#if 0
void Appl::onNewDataRaw(const std::vector<uint8_t> &data)
{
   //TODO
}

void Appl::onNewDataMsg(const DataMsg &msg)
{
   //TODO
}
#endif

/* protected    */

/* public       */


