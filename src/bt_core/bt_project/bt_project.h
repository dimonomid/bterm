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
#include "bt_core.h"



namespace BTCore {
    class Event;
    class DataMsg;
    class ScriptFactory;
}

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
            QString title = ""
            );

    virtual ~Project();

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- project's title
    QString title;

    //-- codec that was given to the project's constructor
    std::shared_ptr<Codec> p_codec;

    //-- JavaScript host BTCore environment
    std::shared_ptr<JSHost> p_jshost;

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

    //-- baudrate that is needed for this project. Will be set to IODev.
    int32_t baudrate;

    //-- true if the project is not saved in its current state;
    //   false otherwise
    bool dirty;

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
     * Return IO device
     */
    std::shared_ptr<IODev> getIODev() const;

    /**
     * Set codec
     * TODO: explain how all_codecs array is used, and how it is created
     * by factory if needed
     */
    void setCurrentCodecNum(CodecNum codec_num);

    /**
     * The project has an array of "known" codecs, i.e. an array of
     * created instances of codecs.
     * TODO: explain more
     */
    void addKnownCodec(std::shared_ptr<Codec> p_codec);

    /**
     * Set needed baudrate. It will be propagated to IODev.:
     *
     */
    void setIODevBaudRate(int32_t baudrate);

    /**
     * Get current baudrate
     */
    int32_t getIODevBaudRate();

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

    /**
     * Returns whether the project is dirty
     */
    bool isDirty();

    /**
     * Set whether the project is dirty
     */
    void setDirty(bool dirty);

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

    /**
     * Emitted whenever dirty/saved status is changed
     */
    void dirtyStatusChanged(bool dirty);

    /**
     * Emitted when script sends a message to the console, using, for example,
     * `console.log()` call.
     *
     * This signal is just forwarded from `#BTCore::JSHost`.
     */
    void scriptMessage(const QString &text, BTCore::MsgLevel level);

private slots:

    void onIODevReadyRead(int bytes_available);
    void onIODevBaudRateChanged(int32_t baudrate);
    void onMessageDecoded(const DataMsg &msg);

    void markDirty();


};


#endif // _BT_PROJECT_H
