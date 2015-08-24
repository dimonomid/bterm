/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>
#include <QJSEngine>
#include <QJSValue>
#include <QtQml>

#include "bt_bytearr_read.h"
#include "bt_bytearr_read_write.h"

#include "bt_jshost.h"
#include "bt_script_factory.h"
#include "bt_script_console.h"



using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

JSHost::JSHost() :
    p_engine(std::make_shared<QJSEngine>()),
    p_script_factory(std::make_shared<ScriptFactory>()),
    script_factory_jsval(p_engine->newQObject(p_script_factory.get())),
    p_script_console(std::make_shared<ScriptConsole>()),
    script_console_jsval(p_engine->newQObject(p_script_console.get())),
    script_ctx_jsval(p_engine->evaluate("({})"))
{
    //-- set ownership of p_script_factory to C++ code, so that JS engine
    //   will never garbage-collect it
    QQmlEngine::setObjectOwnership(
            p_script_factory.get(),
            QQmlEngine::CppOwnership
            );

    initJSEngine();
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

void JSHost::initJSEngine()
{
    p_engine->globalObject().setProperty("LITTLE_END", ByteArrRead::LITTLE_END);
    p_engine->globalObject().setProperty("BIG_END",    ByteArrRead::BIG_END);
    p_engine->globalObject().setProperty("factory",    script_factory_jsval);
    p_engine->globalObject().setProperty("console",    script_console_jsval);
}


/* protected    */

/* public       */

QJSValue JSHost::evaluate(
        const QString &program,
        const QString &file_name,
        int line_number
        )
{
    return p_engine->evaluate(program, file_name, line_number);
}

QJSValue JSHost::getHandlerInputMsgObject(
        std::shared_ptr<std::vector<uint8_t>> p_req_data
        )
{
    //-- create an object that will be given to handlers as input message
    QJSValue input_msg_jsval = p_engine->newObject();

    //-- actual input byte array
    ByteArrRead *p_ba_in = new ByteArrRead(*p_req_data);
    QJSValue ba_in_jsval = p_engine->newQObject(p_ba_in);
    //NOTE: ba_in_jsval is created with QQmlEngine::JavaScriptOwnership,
    //      so, wrapped p_ba_it will be deleted (garbage-collected) by
    //      QJSEngine.

    //QQmlEngine::setObjectOwnership(p_ba_in, QQmlEngine::JavaScriptOwnership);

    input_msg_jsval.setProperty("byteArr", ba_in_jsval);

    return input_msg_jsval;
}

QJSValue JSHost::getScriptContextValue()
{
    return script_ctx_jsval;
}


#if 0
ReqHandler::Result JSHost::runReqHandler(
        std::shared_ptr<ReqHandler> p_handler,
        std::shared_ptr<std::vector<uint8_t>> p_req_data
        )
{
    //-- try to handle the request with current handler
    ReqHandler::Result res = p_handler->handle(
            getHandlerInputMsgObject(p_req_data),
            script_ctx_jsval
            );

    return res;
}
#endif


#if 0
std::shared_ptr<QJSEngine> JSHost::getJSEngine() const
{
    return p_engine;
}
#endif



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */

