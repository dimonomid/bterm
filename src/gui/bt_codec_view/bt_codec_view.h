/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_VIEW_H
#define _BT_CODEC_VIEW_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>




class QDockWidget;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTGui {
    class CodecView;
}

/**
 * Abstract class that represents a GUI view for settings of some
 * particular `#BTCore::Codec`.
 *
 * Not each of the `#BTCore::Codec` subclasses has corresponging
 * view class: if some codec doesn't have any settings, then
 * `#BTGui::CodecEmptyView` is used as a view.
 */
class BTGui::CodecView : public QObject
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:

   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:



   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:

    /**
     * NOTE: each time this function is called, the same widget is returned,
     * and the caller is responsible to delete it eventually.
     *
     * Widget will be actually created at the first call, so if this method
     * never called, then widget is not created at all.
     */
    virtual QWidget *getCodecSettWidget() = 0;



private:

   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/


};


#endif // _BT_CODEC_VIEW_H
