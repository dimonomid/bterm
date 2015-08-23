/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_PROJECT_H
#define _BT_PROJECT_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <memory>

#include <QObject>

#include "bt_iodev.h"
#include "bt_codec.h"
#include "bt_codec_factory.h"
#include "bt_reqhandler.h"



namespace BTCore {
    class Event;
    class DataMsg;
    class ScriptFactory;
}

class QJSEngine;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class Project;
}


/**
 * Class that represents opened project. The project contains
 * name of the codec that is being used (see `#BTCore::Codec`),
 * request handlers, and other things.
 */
class BTCore::Project : public QObject
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
            QString title
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

    //-- all possible codecs
    std::shared_ptr<Codec> all_codecs[
        static_cast<size_t>(CodecNum::_COUNT)
        ];

    //-- IO device being used for communication with outside world
    //   (set by `#BTCore::Project::setIODev()`)
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
     * Set codec
     * TODO: explain how all_codecs array is used, and how it is created
     * by factory if needed
     */
    void setCurrentCodecNum(CodecNum codec_num);

    /**
     * TODO
     */
    void addKnownCodec(std::shared_ptr<Codec> p_codec);

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
     * Remove handler at specified index. After handler is removed, the signal
     * `reqHandlerRemoved()` will be emitted.
     */
    void removeHandler(size_t index);

    /**
     * Get handlers count
     */
    size_t getHandlersCnt() const;

    /**
     * Move hander with specified index "up", i.e. swap it with the previous
     * handler.
     */
    void moveHandlerUp(size_t index);

    /**
     * Move hander with specified index "down", i.e. swap it with the next
     * handler.
     */
    void moveHandlerDown(size_t index);

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
     * Emitted when some event has happened (say, `EventDataRaw` or
     * `EventDataMsg`)
     */
    void event(std::shared_ptr<Event> p_event);

    /**
     * Emitted when title of some request handler has changed.
     *
     * @param p_handler
     *      handler whose title has changed
     * @param name
     *      new title
     */
    void reqHandlerTitleChanged(const ReqHandler *p_handler, const QString &name);

    /**
     * Emitted when new handler was just added to the sequence of handlers.
     *
     * @param p_handler
     *      handler that was just added
     * @param index
     *      index of newly added handler in the sequence of handlers
     */
    void reqHandlerAdded(std::shared_ptr<ReqHandler> p_handler, size_t index);

    /**
     * Emitted when handler was just removed from the sequence of handlers.
     *
     * @param p_handler
     *      handler that was just removed
     * @param index
     *      index of removed handler. When this signal is emitted, this index
     *      is no more occupied by this handler.
     */
    void reqHandlerRemoved(std::shared_ptr<ReqHandler> p_handler, size_t index);

    /**
     * Emitted when handlers are reordered
     */
    void reqHandlersReordered();

    /**
     * Emitted when human-readable title has changed by calling
     * `setTitle()`.
     */
    void titleChanged(const QString &title);

    /**
     * Emitted when current codec is changed by calling `setCurrentCodecNum()`
     */
    void currentCodecNumChanged(std::shared_ptr<Codec> p_codec);

private slots:

    void onDataSrcReadyRead(int bytes_available);
    void onMessageDecoded(const DataMsg &msg);

    void onReqHandlerTitleChanged(const QString &name);


};


#endif // _BT_PROJECT_H
