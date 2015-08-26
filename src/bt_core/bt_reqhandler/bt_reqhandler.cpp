/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtQml>
#include <QJSValue>
#include <QVariant>
#include <QDebug>

#include "bt_bytearr_read.h"
#include "bt_bytearr_read_write.h"
#include "bt_script_factory.h"
#include "my_util.h"
#include "bt_reqhandler.h"
#include "bt_jshost.h"


using namespace BTCore;

/****************************************************************************
 * CONSTANTS
 ***************************************************************************/

const size_t ReqHandler::INDEX_UNKNOWN = (size_t)-1;



/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ReqHandler::ReqHandler(
        QString title,
        std::shared_ptr<JSHost> p_jshost,
        QString script_func_code
        ) :
    title(title),
    p_jshost(p_jshost),
    script_func_code(),
    last_error(Error::UNKNOWN),
    last_exception_details(),
    handler_index(INDEX_UNKNOWN)
{
    setScript(script_func_code);
}

ReqHandler::ReqHandler(
        QString title,
        QString script_func_code
        ) :
    ReqHandler(
            title,
            std::shared_ptr<JSHost>(),
            script_func_code
            )
{

}

ReqHandler::ReqHandler() :
    ReqHandler(
            "Untitled handler",
            std::shared_ptr<JSHost>(),
            "(function(inputMsg){ \n"
            "    var handled = false;\n"
            "    var outputArr;\n"
            "\n"
            "    if (false /*inputMsg.byteArr.getU08(0) === 0x01*/){\n"
            "        outputArr = factory.createByteArr();\n"
            "        outputArr\n"
            "            .putU08(1, 0x04)\n"
            "            .putU16(4, 0x1234)\n"
            "            ;\n"
            "\n"
            "        io.writeEncoded(outputArr);\n"
            "\n"
            "        handled = true;\n"
            "    };\n"
            "\n"
            "    return {\n"
            "       handled: handled\n"
            "    };\n"
            " })\n"
            )
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

void ReqHandler::setJSHost(std::shared_ptr<JSHost> p_jshost)
{
    this->p_jshost = p_jshost;
}

QString ReqHandler::getTitle() const
{
    return title;
}

void ReqHandler::setTitle(const QString &title)
{
    this->title = title;
    emit titleChanged(this->title);
}

QString ReqHandler::getScript() const
{
    return script_func_code;
}

void ReqHandler::setScript(QString script_func_code)
{
    this->script_func_code = script_func_code;

    //-- set handler_func to default (undefined) value, so that next time
    //   the handler is called, it will be evaluated from `script_func_code`
    handler_func = QJSValue();

    emit scriptChanged(this->script_func_code);
}

ReqHandler::Result ReqHandler::handle(
        QJSValue input_msg_jsval
        )
{
    //-- before handling, set global properties

    ReqHandler::Result ret = Result::UNKNOWN;

    last_error = Error::UNKNOWN;
    last_exception_details = QVariantMap();

    QJSValue result;



    //-- check if we already have evaluated handler function
    if (!handler_func.isCallable()){
        //-- no, so, try to evaluate JavaScript code
        handler_func = p_jshost->evaluate(
                script_func_code,
                this->title
                );
    }

    if (handler_func.isError()){
        //-- evaluation is failed: some error in JavaScript code.

        ret = Result::ERROR;
        last_error = Error::EXCEPTION;
        last_exception_details = MyUtil::qjsErrorToVariant(handler_func);
        qDebug() << "exception 1: " << last_exception_details;

    } else if (!handler_func.isCallable()){
        //-- evaluation has succeed, but the script has evaluated to
        //   non-function value.

        ret = Result::ERROR;
        last_error = Error::SCRIPT_IS_NOT_FUNCTION;

    } else {

        //-- ok, we have function value. Try to call it,
        //   passing the scripts context as `this`.
        QJSValue returned = p_jshost->callFuncWithCommonContext(
                handler_func,
                QJSValueList() << input_msg_jsval,
                this->title
                );


        if (returned.isError()){
            //-- returned value is an error: some exception has happened
            //   during handler invocation

            ret = Result::ERROR;
            last_error = Error::EXCEPTION;
            last_exception_details = MyUtil::qjsErrorToVariant(returned);
            qDebug() << "exception 2: " << last_exception_details;
        } else {
            //-- ok, handler has executed successfully. Let's see the result:
            //   whether the request was handled or not.

            bool handled = returned.property("handled").toBool();
            ret = handled ? Result::OK_HANDLED : Result::OK_NOT_HANDLED;

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

void ReqHandler::setHandlerIndex(size_t index)
{
    handler_index = index;
}

size_t ReqHandler::getHandlerIndex()
{
    return handler_index;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


