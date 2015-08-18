/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HTCODEC_H
#define _HTCODEC_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>

#include <QObject>
#include "htdatamsg.h"

#include <vector>



class QJSEngine;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class Codec;
}

/**
 * TODO
 */
class HTCore::Codec : public QObject
{
Q_OBJECT

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    Codec(
            std::shared_ptr<QJSEngine> p_engine
         );


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    std::shared_ptr<QJSEngine> p_engine;
    QJSValue codec_js;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:
    void     addRawRxData   (const std::vector<uint8_t> &data);
    void     clearRawRxData ();
    DataMsg  encodeMessage  (const std::vector<uint8_t> &data) const;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

signals:
    void messageDecoded(const DataMsg &msg);
    //void curMessageChanged(const DTMsg &msg);
    //void invalidDataDetected(const QByteArray &data);

};


#endif // _HTCODEC_H
