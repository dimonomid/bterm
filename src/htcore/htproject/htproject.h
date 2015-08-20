/*******************************************************************************
 *   Description:   TODO
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
    explicit Project(
            QString title,
            std::shared_ptr<Codec> p_codec
            );

    virtual ~Project();

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    QString title;

    std::shared_ptr<QJSEngine> p_engine;
    std::shared_ptr<ScriptFactory> p_script_factory;

    std::shared_ptr<Codec> p_codec;
    std::shared_ptr<IODev> p_io_dev;

    std::vector<std::shared_ptr<ReqHandler>> handlers;
    QJSValue script_ctx_jsval;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    void setIODev(std::shared_ptr<IODev> p_io_dev);
    void addHandler(std::shared_ptr<ReqHandler> p_handler);
    std::shared_ptr<ReqHandler> getHandler(size_t index);
    size_t getHandlersCnt() const;

    std::shared_ptr<Codec> getCodec() const;

    QString getTitle() const;
    void setTitle(QString title);

private:



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:
    void eventDataRaw(std::shared_ptr<EventDataRaw> p_event);
    void eventDataMsg(std::shared_ptr<EventDataMsg> p_event);

    void reqHandlerNameChanged(const ReqHandler *p_handler, const QString &name);



private slots:
    void onDataSrcReadyRead(int bytes_available);
    void onMessageDecoded(const DataMsg &msg);

    void onReqHandlerNameChanged(const QString &name);


};


#endif // _HTPROJECT_H
