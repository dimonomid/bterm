/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_EMPTY_VIEW_H
#define _BT_CODEC_EMPTY_VIEW_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>

#include "bt_codec_view.h"




/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTGui {
    class CodecEmptyView;
}

/**
 * TODO
 */
class BTGui::CodecEmptyView : public BTGui::CodecView
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    explicit CodecEmptyView(QString codec_name);


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    QString codec_name;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual QWidget *getCodecSettWidget() override;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_CODEC_EMPTY_VIEW_H
