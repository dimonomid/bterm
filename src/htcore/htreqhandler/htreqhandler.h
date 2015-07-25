/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HTREQHANDLER_H
#define _HTREQHANDLER_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QString>
#include <QScriptValue>

#include <memory>


class QScriptEngine;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
   class ReqHandler;
}

/**
 * Response generator
 * TODO
 */
class HTCore::ReqHandler
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/
public:

   enum class Result {
      UNKNOWN,
      OK_NOT_HANDLED,
      OK_HANDLED,
      ERROR,
   };

   enum class Error {
      UNKNOWN,
      SCRIPT_IS_NOT_FUNCTION,
      EXCEPTION,
   };

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   ReqHandler(
         QString name,
         std::shared_ptr<QScriptEngine> p_engine,
         QString script_func_code = ""
         );


   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

   QString name;
   std::shared_ptr<QScriptEngine> p_engine;
   QString script_func_code;
   Error last_error;
   std::shared_ptr<ByteArrReadWrite> p_response;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:

   QString getName() const;
   void setScript(QString script_func_code);

   /**
    * TODO
    */
   Result handle(
         std::shared_ptr<std::vector<uint8_t>> p_data,
         QScriptValue chain_data
         );

   /**
    * If latest `#HTCore::ReqHandler::handle()` call returned
    * `#HTCore::ReqHandler::Result::OK_HANDLED`, then this method returns
    * response that was generated by the handler script.
    */
   std::shared_ptr<std::vector<uint8_t>> p_data getResponse();


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/

};


#endif // _HTREQHANDLER_H
