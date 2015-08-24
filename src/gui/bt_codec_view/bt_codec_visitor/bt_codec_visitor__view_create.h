/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CODEC_VISITOR__VIEW_CREATE_H
#define _BT_CODEC_VISITOR__VIEW_CREATE_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec_visitor.h"

#include <QDomElement>
#include <memory>


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTGui {
    class CodecVisitor_ViewCreate;
    class CodecView;
}

/**
 * Concrete visitor for `#BTCore::Codec`, it creates the view for codec
 * settings, depending on exact Codec subclass.
 */
class BTGui::CodecVisitor_ViewCreate : public BTCore::CodecVisitor
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    CodecVisitor_ViewCreate();


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- codec view that is created during visitor acceptance
    std::shared_ptr<BTGui::CodecView> p_codec_view;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    virtual void visit(BTCore::Codec_ISO14230 &) override;
    virtual void visit(BTCore::CodecTransparent &) override;

    /**
     * Returns the `#BTGui::CodecView` created for the given
     * `#BTCore::Codec` during the visitor acceptance.
     */
    std::shared_ptr<BTGui::CodecView> getCodecView();
};


#endif // _BT_CODEC_VISITOR__VIEW_CREATE_H
