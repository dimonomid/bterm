/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_REQHANDLER_H
#define _BT_REQHANDLER_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QString>
#include <QJSValue>
#include <QVariantMap>

#include <memory>


namespace BTCore {
    class JSHost;
    class ScriptFactory;
    class ByteArrReadWrite;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class ReqHandler;
}

/**
 * Class that represents single handler of the incoming message (request).
 * The handler's behavior is defined by JavaScript code.
 *
 * TODO: explain handler's JavaScript API
 */
class BTCore::ReqHandler : public QObject
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/
public:

    /**
     * Handling result
     */
    enum class Result {
        /** Should never be returned: the result is unknown.
         */
        UNKNOWN,

        /** There were no errors during execution of handler, and the request
         * was not handled by this particular handler.
         */
        OK_NOT_HANDLED,

        /** There were no errors during execution of handler, and the request
         * was handled by this handler. So, the caller should get generated
         * response from this handler, encode it, and send it on the wire (if
         * it is not empty)
         */
        OK_HANDLED,

        /** There was some JavaScript error during execution of this handler.
         * Consult `getLastError()` function to get more
         * specific error.
         */
        ERROR,
    };

    /**
     * Kind of error, when `#Result` is `Result::ERROR`
     */
    enum class Error {
        /** Unknown error: this code is returned if the handling result was not
         * `Result::ERROR`.
         */
        UNKNOWN,

        /** The given JavaScript evaluates to some non-function value.
         */
        SCRIPT_IS_NOT_FUNCTION,

        /** Exception has happened during JavaScript code execution.  Consult
         * `#getLastExceptionDetails()` function to get
         * details of the exception.
         */
        EXCEPTION,
    };




    /****************************************************************************
     * CONSTANTS
     ***************************************************************************/
public:

    static const size_t INDEX_UNKNOWN;



    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    /**
     * Construct request handler with all the necessary data specified
     *
     * @param title
     *      human-readable title of the handler
     * @param p_jshost
     *      JavaScript host (see `#BTCore::JSHost`)
     * @param script_func_code
     *      JavaScript code to execute as a handler
     */
    ReqHandler(
            QString title,
            std::shared_ptr<JSHost> p_jshost,
            QString script_func_code
            );

    /**
     * Construct request handler without JavaScript host environment specified.
     * It should be set later by calling `setJSHost()`
     * and `setScriptFactory()`.
     *
     * @param title
     *      human-readable title of the handler
     * @param script_func_code
     *      JavaScript code to execute as a handler
     */
    ReqHandler(
            QString title,
            QString script_func_code = ""
            );

    /**
     * Construct request handler with default title "Untitled handler" and
     * script draft. JavaScript host environment should be set later by
     * calling `setJSHost()`
     */
    ReqHandler();

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- human-readable handler title
    QString title;

    //-- JavaScript engine
    std::shared_ptr<JSHost> p_jshost;

    //-- JavaScript handler code
    QString script_func_code;

    //-- Error that happened during last call of
    //   `#handle()`. Valid if only `handle()` returned
    //   `#Result::ERROR`.
    Error last_error;

    //-- Details of exception that has happened during last call of
    //   `#handle()`. Valid if only `handle()` returned
    //   `Result::ERROR`, and `last_error` is `EXCEPTION`.
    QVariantMap last_exception_details;

    //-- index of this handler in the handlers sequence. By default set to
    //   `INDEX_UNKNOWN`, should be overridden later by calling
    //   `setHandlerIndex()`.
    size_t handler_index;

    //-- actual handler function. It is evaluated from `script_func_code`.
    QJSValue handler_func;

    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * Set JavaScript engine to use
     */
    void setJSHost(std::shared_ptr<JSHost> p_jshost);

    /**
     * Get human-readable title of the handler
     */
    QString getTitle() const;

    /**
     * Set human-readable title of the handler
     */
    void setTitle(const QString &title);

    /**
     * Get JavaScript handler code
     */
    QString getScript() const;

    /**
     * Set JavaScript handler code
     *
     * TODO: explain handler's JavaScript API
     */
    void setScript(QString script_func_code);

    /**
     * Handle the request.
     *
     * @param input_msg_jsval
     *      JavaScript object that represents input data.  This object should
     *      have property "byteArr", which should be set to
     *      `BTCore::ByteArrRead` instance (of course, wrapped into `QJSValue`
     *      object).
     *
     *      It may also have some other codec-specific properties, so that
     *      handlers have access to them.
     */
    Result handle(
            QJSValue input_msg_jsval
            );

    /**
     * Error that happened during last call of `handle()`.
     * Valid if only `handle()` returned `Result::ERROR`.
     */
    Error getLastError();

    /**
     * Details of exception that has happened during last call of
     * `handle()`. Valid if only `handle()` returned
     * `Result::ERROR`, and
     * `getLastError()` returned
     * `Error::EXCEPTION`.
     */
    QVariantMap getLastExceptionDetails();

    /**
     * Set index of this handler in the handlers sequence
     */
    void setHandlerIndex(size_t index);

    /**
     * Get index of this handler in the handlers sequence. When handler is just
     * created, the index is set to `INDEX_UNKNOWN`, so, if nobody
     * calls `setHandlerIndex()`, this function will return `INDEX_UNKNOWN`.
     */
    size_t getHandlerIndex();


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

signals:

    /**
     * Emitted when human-readable title has changed by calling
     * `setTitle()`.
     */
    void titleChanged(const QString &title);


    /**
     * Emitted when script is changed by calling `setScript()`
     */
    void scriptChanged(const QString &script);
};


#endif // _BT_REQHANDLER_H
