/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QLabel>

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
    return new QLabel(
            "The codec \"" + codec_name + "\" doesn't have any settings"
            );
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


