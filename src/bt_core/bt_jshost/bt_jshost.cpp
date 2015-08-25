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

    //-- setup host-specific environment for scripts
    initJSEngine();

    //-- forward `console.log()` calls with signal `scriptMessage()`
    connect(
            p_script_console.get(), &ScriptConsole::message,
            this, &JSHost::scriptMessage
           );
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
    //TODO: add comments about these registrations
    //
    //   It seems, we register ByteArrRead as non-instantiable type,
    //   and ByteArrReadWrite as instantiable
    qmlRegisterType<ByteArrRead>     ();
    qmlRegisterType<ByteArrReadWrite>("", 1, 0, "ByteArrReadWrite");

    //-- set host properties
    setGlobalFrozenProperty("LITTLE_END", ByteArrRead::LITTLE_END);
    setGlobalFrozenProperty("BIG_END",    ByteArrRead::BIG_END);
    setGlobalFrozenProperty("factory",    script_factory_jsval);
    setGlobalFrozenProperty("console",    script_console_jsval);

}


/* protected    */

/* public       */

QJSValue JSHost::evaluate(
        const QString &program,
        const QString &file_name,
        int line_number
        )
{
    return p_engine->evaluate(
            "'use strict'; " + program,
            file_name,
            line_number
            );
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





/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


