/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_ISO14230_VIEW_H
#define _BT_CODEC_ISO14230_VIEW_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>

#include "bt_codec_view.h"
#include "ui_bt_codec_iso14230_view.h"



namespace BTCore {
    class Codec_ISO14230;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTGui {
    class CodecISO14230View;
}

/**
 * A subclass of `#BTGui::CodecView` that represents GUI object for
 * `#BTCore::Codec_ISO14230`.
 */
class BTGui::CodecISO14230View : public BTGui::CodecView
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    explicit CodecISO14230View(
            std::shared_ptr<BTCore::Codec_ISO14230> p_codec_iso14230
            );


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- auto-generated UI class (by Qt Designer)
    Ui::BTCodecISO14230View *p_codec_iso14230_view_ui;
    std::shared_ptr<BTCore::Codec_ISO14230> p_codec_iso14230;
    QWidget *p_codec_sett_widg;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual QWidget *getCodecSettWidget() override;



private:

    QWidget *createSettWidget();


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

private slots:

    void onFmtRxChangedByUser(int value);
    void onLocalAddrRxChangedByUser(int value);
    void onRemoteAddrRxChangedByUser(int value);
    void onFmtTxChangedByUser(int value);
    void onLocalAddrTxChangedByUser(int value);
    void onRemoteAddrTxChangedByUser(int value);

    void onWidgetDestroyed();
};


#endif // _BT_CODEC_ISO14230_VIEW_H
