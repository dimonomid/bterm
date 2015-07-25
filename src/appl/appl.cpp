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

      ByteArr ba_in {};
      ByteArr ba_out {};

      QScriptValue ba_in_scrval = engine.newQObject(&ba_in);
      QScriptValue ba_out_scrval = engine.newQObject(&ba_out);
      QScriptValue chain_data_scrval = engine.evaluate("({})");

      ba_in.putU08(0, 0x61);
      ba_in.putU08(1, 0x01);

      QScriptValue func = engine.evaluate(
            "(function(inputArr, outputArr){ "
            "     this.c = 123;"

            "     if (inputArr.getU08(0) === 0x61){"
            "        outputArr.putU08(4, 0x10);"
            "        outputArr.putU08(1, 0xff);"
            "     };"
            "     return {"
            "        handled: true"
            "     };"
            " })"
      );
      QScriptValue returned = func.call(
            chain_data_scrval,
            QScriptValueList() << ba_in_scrval << ba_out_scrval << chain_data_scrval
            );

      qDebug() << "in: "  << MyUtil::byteArrayToHex(*ba_in.getData());
      qDebug() << "out: " << MyUtil::byteArrayToHex(*ba_out.getData());
      qDebug() << "chainData: " << chain_data_scrval.toVariant().toMap();

      if (engine.hasUncaughtException()){
         qDebug() << "exception: " << returned.toVariant();
      } else {
         qDebug() << "returned: " << returned.toVariant();
         qDebug() << "returned handled: " << returned.toVariant().toMap()["handled"].toBool();
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


