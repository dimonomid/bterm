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
#include "bt_script_io.h"



using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

JSHost::JSHost(
        std::shared_ptr<Project> p_project
        ) :
    wp_project(p_project),
    p_engine(std::make_shared<QJSEngine>()),
    p_script_factory(std::make_shared<ScriptFactory>()),
    script_factory_jsval(p_engine->newQObject(p_script_factory.get())),
    p_script_console(std::make_shared<ScriptConsole>()),
    script_console_jsval(p_engine->newQObject(p_script_console.get())),

    //TODO: will be initialized later
    p_script_io(),
    script_io_jsval(),

    script_ctx_jsval(p_engine->evaluate("({})"))
{
    //-- real initialization will be done later, in `init()` method,
    //   called by factory static method `create()`
}




/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */

std::shared_ptr<JSHost> JSHost::create(
        std::shared_ptr<Project> p_project
        )
{
    //-- NOTE: we can't use std::make_shared, since Project constructor
    //   is private
    std::shared_ptr<JSHost> p_jshost {new JSHost(p_project)};
    p_jshost->init(p_project);

    return p_jshost;
}





/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

void JSHost::init(
        std::shared_ptr<Project> p_project
        )
{
    p_script_io = std::make_shared<ScriptIO>(p_project, getSharedPtr());
    script_io_jsval = p_engine->newQObject(p_script_io.get());

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


void JSHost::initJSEngine()
{
    //TODO: add comments about these registrations
    //
    //   It seems, we register ByteArrRead as non-instantiable type,
    //   and ByteArrReadWrite as instantiable

    //-- We need to register types that are used as return or argument types
    //   in `Q_INVOKABLE` methods.
    //   NOTE that in the header file, you must specify these types
    //   as fully-qualified ones: so, not just `ByteArrRead`,
    //   but `BTCore::ByteArrRead`. Otherwise, QJSEngine complains about
    //   unknown type.
    qmlRegisterType<ByteArrRead>     ();

    //-- register instantiable type: it should have default ctor
    qmlRegisterType<ByteArrReadWrite>("", 1, 0, "ByteArrReadWrite");

    //-- register non-instantiable type ScriptIO
    qmlRegisterType<ScriptIO>        ();

    //-- set host properties
    setGlobalFrozenProperty("LITTLE_END", ByteArrRead::LITTLE_END);
    setGlobalFrozenProperty("BIG_END",    ByteArrRead::BIG_END);
    setGlobalFrozenProperty("factory",    script_factory_jsval);
    setGlobalFrozenProperty("console",    script_console_jsval);
    setGlobalFrozenProperty("io",         script_io_jsval);

}


/* protected    */

/* public       */

std::shared_ptr<JSHost> JSHost::getSharedPtr()
{
    return shared_from_this();
}


QJSValue JSHost::evaluate(
        const QString &program,
        const QString &file_name,
        int line_number
        )
{
    QJSValue ret = p_engine->evaluate(
            "'use strict'; " + program,
            file_name,
            line_number
            );

    return ret;
}

QJSValue JSHost::callFuncWithInstance(
        QJSValue func,
        QJSValue instance,
        QJSValueList arguments,
        QString descr
        )
{
    cur_script_descr = descr;

    QJSValue ret = func.callWithInstance(
            instance,
            arguments
            );

    cur_script_descr = "";

    return ret;
}

QJSValue JSHost::callFuncWithCommonContext(
        QJSValue func,
        QJSValueList arguments,
        QString descr
        )
{
    return callFuncWithInstance(
            func,
            script_ctx_jsval,
            arguments,
            descr
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

QString JSHost::getCurrentScriptDescr()
{
    return cur_script_descr;
}




/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


