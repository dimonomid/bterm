/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QLabel>
#include <QBoxLayout>

#include "bt_codec_empty_view.h"
//#include "ui_bt_codec_empty_view.h"



using namespace BTGui;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

CodecEmptyView::CodecEmptyView(QString codec_name) :
    codec_name(codec_name)
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

QWidget *CodecEmptyView::getCodecSettWidget()
{
    QWidget *p_ret = new QWidget();

    QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);

    p_lay->addWidget(
            new QLabel(
                "The codec \"" + codec_name + "\" doesn't have any settings"
                )
            );

    p_lay->addStretch(0);

    p_ret->setLayout(p_lay);

    return p_ret;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


