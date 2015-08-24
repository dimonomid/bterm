/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_JSHOST_H
#define _BT_JSHOST_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <QJSValue>
#include <QJSEngine>

#include <memory>
#include <vector>

#include "bt_reqhandler.h"
#include "bt_core.h"



namespace BTCore {
    class ScriptFactory;
    class ScriptConsole;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class JSHost;
}


/**
 * Class that represents JavaScript host environment for `BTCore`.
 */
class BTCore::JSHost : public QObject
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    explicit JSHost();


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- JavaScript engine
    std::shared_ptr<QJSEngine> p_engine;

    //-- factory that is used by scripts in order to create
    //   instances of various types.
    std::shared_ptr<ScriptFactory> p_script_factory;

    //-- the same factory wrapped inside QJSValue
    QJSValue script_factory_jsval;

    //-- console object that is used by scripts
    std::shared_ptr<ScriptConsole> p_script_console;

    //-- the same factory wrapped inside QJSValue
    QJSValue script_console_jsval;


    //-- context that is used by script functions. It is given as `this`
    //   argument to each function.
    QJSValue script_ctx_jsval;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * Call `QJSEngine::evaluate()` on host-specific `QJSEngine` instance.
     */
    QJSValue evaluate(
            const QString &program,
            const QString &file_name = QString(),
            int line_number = 1
            );

    /**
     * Create and return JavaScript object that should be given
     * as input message for request handler (`#BTCore::ReqHandler`)
     */
    QJSValue getHandlerInputMsgObject(
            std::shared_ptr<std::vector<uint8_t>> p_req_data
            );

    /**
     * Returns context that is used as `this` in JavaScript handler functions
     */
    QJSValue getScriptContextValue();

#if 0
    /**
     * Run given request handler for given p_req_data, using this JavaScript
     * host environment.
     */
    ReqHandler::Result runReqHandler(
            std::shared_ptr<ReqHandler> p_handler,
            std::shared_ptr<std::vector<uint8_t>> p_req_data
            );
#endif

#if 0
    std::shared_ptr<QJSEngine> getJSEngine() const;
#endif



private:

    /**
     * Put some host-specific properties on JSEngine
     */
    void initJSEngine();

    /**
     * Set frozen property on global object. User won't be able
     * to do anything with this property but read it.
     */
    template<class T>
    void setGlobalFrozenProperty(const QString &prop_name, T value)
    {
        //-- set property on global object
        p_engine->globalObject().setProperty(prop_name, value);

        //-- make it frozen (we have to evaluate script for that,
        //   since QJSEngine doesn't expose a C++ API for that)
        p_engine->evaluate(
                "Object.defineProperty("
                "   this,"
                "   \"" + prop_name + "\","
                "   { writable: false, enumerable: false, configurable: false }"
                ");"
                );
    }



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

signals:

    /**
     * Emitted when script sends a message to the console, using, for example,
     * `console.log()` call.
     */
    void scriptMessage(const QString &text, BTCore::MsgLevel level);


};


#endif // _BT_JSHOST_H
