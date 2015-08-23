/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QLabel>

#include "bt_codec_iso14230_view.h"
#include "bt_codec_iso14230.h"



using namespace BTCore;
using namespace BTGui;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

CodecISO14230View::CodecISO14230View(
        std::shared_ptr<BTCore::Codec_ISO14230> p_codec_iso14230
        ) :
    p_codec_iso14230_view_ui(new Ui::BTCodecISO14230View),
    p_codec_iso14230(p_codec_iso14230),
    p_codec_sett_widg()
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

QWidget *CodecISO14230View::createSettWidget()
{
    QWidget *p_widg = new QWidget();

    p_codec_iso14230_view_ui->setupUi(p_widg);

    //-- set current data
    p_codec_iso14230_view_ui->fmt_rx->setValue(
            p_codec_iso14230->getFmtRx()
            );
    p_codec_iso14230_view_ui->local_addr_rx->setValue(
            p_codec_iso14230->getOwnAddrRx()
            );
    p_codec_iso14230_view_ui->remote_addr_rx->setValue(
            p_codec_iso14230->getRemoteAddrRx()
            );
    p_codec_iso14230_view_ui->fmt_tx->setValue(
            p_codec_iso14230->getFmtTx()
            );
    p_codec_iso14230_view_ui->local_addr_tx->setValue(
            p_codec_iso14230->getOwnAddrTx()
            );
    p_codec_iso14230_view_ui->remote_addr_tx->setValue(
            p_codec_iso14230->getRemoteAddrTx()
            );




    //-- listen for widget destroy event
    connect(
            p_widg, &QObject::destroyed,
            this, &CodecISO14230View::onWidgetDestroyed
           );

    return p_widg;
}

/* protected    */

/* public       */

QWidget *CodecISO14230View::getCodecSettWidget()
{
    if (p_codec_sett_widg == nullptr){
        p_codec_sett_widg = createSettWidget();
    }

    return p_codec_sett_widg;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void CodecISO14230View::onWidgetDestroyed()
{
    p_codec_sett_widg = nullptr;
}

/* protected    */

/* public       */


