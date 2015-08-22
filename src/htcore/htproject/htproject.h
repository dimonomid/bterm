/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HTPROJECT_H
#define _HTPROJECT_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <memory>

#include <QObject>

#include "htiodev.h"
#include "htcodec.h"
#include "htreqhandler.h"



namespace HTCore {
    class EventDataRaw;
    class EventDataMsg;
    class DataMsg;
    class ScriptFactory;
}

class QJSEngine;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class Project;
}


/**
 * Class that represents opened project. The project contains
 * name of the codec that is being used (see `#HTCore::Codec`),
 * request handlers, and other things.
 */
class HTCore::Project : public QObject
{
Q_OBJECT

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    /**
     * Constructs the project with given title and codec.
     */
    explicit Project(
            QString title,
            std::shared_ptr<Codec> p_codec
            );

    virtual ~Project();

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- project's title
    QString title;

    //-- JavaScript engine, it is shared across all req handlers
    std::shared_ptr<QJSEngine> p_engine;
    //-- factory that is used by scripts in order to create
    //   instances of various types.
    std::shared_ptr<ScriptFactory> p_script_factory;

    //-- codec that was given to the project's constructor
    std::shared_ptr<Codec> p_codec;
    //-- IO device being used for communication with outside world
    //   (set by `#HTCore::Project::setIODev()`)
    std::shared_ptr<IODev> p_io_dev;

    //-- sequence of handlers, they get executed sequentially
    //   when new message arrives
    std::vector<std::shared_ptr<ReqHandler>> handlers;

    //-- context that is used by handlers. It is given as `this`
    //   argument to each handler function.
    QJSValue script_ctx_jsval;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * Set IO device, so that we can communicate with outside world
     */
    void setIODev(std::shared_ptr<IODev> p_io_dev);

    /**
     * Add new handler to the end of the sequence of handlers.
     */
    void addHandler(std::shared_ptr<ReqHandler> p_handler);

    /**
     * Get handler at specified index. If index is too large,
     * empty shared_ptr is returned.
     */
    std::shared_ptr<ReqHandler> getHandler(size_t index);

    /**
     * Get handlers count
     */
    size_t getHandlersCnt() const;

    /**
     * Get codec being currently used by the project
     */
    std::shared_ptr<Codec> getCodec() const;

    /**
     * Get project's title
     */
    QString getTitle() const;

    /**
     * Set project's title
     */
    void setTitle(QString title);

private:



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:

    /**
     * Emitted when `EventDataRaw` happened
     */
    void eventDataRaw(std::shared_ptr<EventDataRaw> p_event);

    /**
     * Emitted when `EventDataMsg` happened
     */
    void eventDataMsg(std::shared_ptr<EventDataMsg> p_event);

    /**
     * Emitted when title of some request handler has changed.
     *
     * @param p_handler
     *      handler whose title has changed
     * @param name
     *      new title
     */
    void reqHandlerTitleChanged(const ReqHandler *p_handler, const QString &name);



private slots:

    void onDataSrcReadyRead(int bytes_available);
    void onMessageDecoded(const DataMsg &msg);

    void onReqHandlerTitleChanged(const QString &name);


};


#endif // _HTPROJECT_H
