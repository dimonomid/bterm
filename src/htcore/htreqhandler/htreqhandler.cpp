/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QScriptEngine>
#include <QScriptValue>
#include <QVariant>
#include <QDebug>

#include "bytearr_read.h"
#include "bytearr_read_write.h"
#include "my_util.h"
#include "htreqhandler.h"


using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ReqHandler::ReqHandler(
      QString name,
      std::shared_ptr<QScriptEngine> p_engine,
      QString script_func_code
      ) :
   name(name),
   p_engine(p_engine),
   script_func_code(script_func_code),
   last_error(Error::UNKNOWN),
   p_response()
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

QString ReqHandler::getName() const
{
   return name;
}

void ReqHandler::setScript(QString script_func_code)
{
   this->script_func_code = script_func_code;
}

ReqHandler::Result ReqHandler::handle(
      std::shared_ptr<std::vector<uint8_t>> p_data,
      QScriptValue chain_data
      )
{
   ReqHandler::Result ret = Result::UNKNOWN;

   last_error = Error::UNKNOWN;

   QScriptValue result;

   ByteArrRead ba_in {*p_data};
   p_response = std::make_shared<ByteArrReadWrite>();

   QScriptValue ba_in_scrval = p_engine->newQObject(&ba_in);
   QScriptValue ba_out_scrval = p_engine->newQObject(p_response);

   QScriptValue func = p_engine->evaluate(script_func_code);

   if (p_engine->hasUncaughtException()){

      ret = Result::ERROR;
      last_error = Error::EXCEPTION;
      //TODO: save exception
      qDebug() << "exception: " << func.toVariant();

   } else if (!func.isFunction()){

      ret = Result::ERROR;
      last_error = Error::SCRIPT_IS_NOT_FUNCTION;

   } else {

      QScriptValue returned = func.call(
            chain_data,
            QScriptValueList() << ba_in_scrval << ba_out_scrval
            );

      if (p_engine->hasUncaughtException()){
         ret = Result::ERROR;
         last_error = Error::EXCEPTION;
         //TODO: save exception
         qDebug() << "exception: " << func.toVariant();
      } else {
         bool handled = returned.toVariant().toMap()["handled"].toBool();
         if (handled){
            ret = Result::OK_HANDLED;
            //-- p_response now contains the byte array that was written by the script
         } else {
            ret = Result::OK_NOT_HANDLED;
         }
      }

   }

   return ret;
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


