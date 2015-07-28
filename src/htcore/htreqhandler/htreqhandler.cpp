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
   p_response(),
   last_exception_details()
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
      const std::vector<uint8_t> &data,
      QScriptValue script_ctx
      )
{
   //-- before handling, set global properties
   p_engine->globalObject().setProperty("LITTLE_END", ByteArrRead::LITTLE_END);
   p_engine->globalObject().setProperty("BIG_END",    ByteArrRead::BIG_END);

   ReqHandler::Result ret = Result::UNKNOWN;

   last_error = Error::UNKNOWN;
   last_exception_details = QVariantMap();

   QScriptValue result;

   ByteArrRead ba_in {data};
   p_response = std::make_shared<ByteArrReadWrite>();

   QScriptValue ba_in_scrval = p_engine->newQObject(&ba_in);
   QScriptValue ba_out_scrval = p_engine->newQObject(p_response.get());

   QScriptValue func = p_engine->evaluate(script_func_code);

   if (p_engine->hasUncaughtException()){

      ret = Result::ERROR;
      last_error = Error::EXCEPTION;
      last_exception_details = func.toVariant().toMap();
      qDebug() << "exception 1: " << func.toVariant();

   } else if (!func.isFunction()){

      ret = Result::ERROR;
      last_error = Error::SCRIPT_IS_NOT_FUNCTION;

   } else {

      QScriptValue returned = func.call(
            script_ctx,
            QScriptValueList() << ba_in_scrval << ba_out_scrval
            );

      if (p_engine->hasUncaughtException()){
         ret = Result::ERROR;
         last_error = Error::EXCEPTION;
         last_exception_details = func.toVariant().toMap();
         qDebug() << "exception 2: " << func.toVariant();
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

ReqHandler::Error ReqHandler::getLastError()
{
   return last_error;
}

QVariantMap ReqHandler::getLastExceptionDetails()
{
   return last_exception_details;
}

std::shared_ptr<const std::vector<uint8_t>> ReqHandler::getResponse()
{
   return p_response->getData();
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


