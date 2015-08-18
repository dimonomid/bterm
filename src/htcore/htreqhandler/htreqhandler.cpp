/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtQml>
#include <QJSEngine>
#include <QJSValue>
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
      std::shared_ptr<QJSEngine> p_engine,
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

QString ReqHandler::getScript() const
{
   return script_func_code;
}

void ReqHandler::setScript(QString script_func_code)
{
   this->script_func_code = script_func_code;
}

ReqHandler::Result ReqHandler::handle(
      QJSValue input_msg_jsval,
      QJSValue script_ctx_jsval
      )
{
   //-- before handling, set global properties
   p_engine->globalObject().setProperty("LITTLE_END", ByteArrRead::LITTLE_END);
   p_engine->globalObject().setProperty("BIG_END",    ByteArrRead::BIG_END);

   ReqHandler::Result ret = Result::UNKNOWN;

   last_error = Error::UNKNOWN;
   last_exception_details = QVariantMap();

   QJSValue result;

   p_response = std::make_shared<ByteArrReadWrite>();

   QJSValue ba_out_scrval = p_engine->newQObject(p_response.get());
   QQmlEngine::setObjectOwnership(p_response.get(), QQmlEngine::CppOwnership);


   QJSValue func = p_engine->evaluate(script_func_code);

   if (func.isError()){

      ret = Result::ERROR;
      last_error = Error::EXCEPTION;
      last_exception_details = MyUtil::qjsErrorToVariant(func);
      qDebug() << "exception 1: " << last_exception_details;

   } else if (!func.isCallable()){

      ret = Result::ERROR;
      last_error = Error::SCRIPT_IS_NOT_FUNCTION;

   } else {

      QJSValue returned = func.callWithInstance(
            script_ctx_jsval,
            QJSValueList() << input_msg_jsval << ba_out_scrval
            );

      if (returned.isError()){
         ret = Result::ERROR;
         last_error = Error::EXCEPTION;
         last_exception_details = MyUtil::qjsErrorToVariant(returned);
         qDebug() << "exception 2: " << last_exception_details;
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


