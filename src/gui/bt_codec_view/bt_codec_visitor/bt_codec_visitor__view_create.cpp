/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_codec_visitor__view_create.h"
#include "bt_project_storage_xml.h"
#include "bt_codec_iso14230.h"
#include "bt_codec_factory.h"

#include "bt_codec_empty_view.h"
#include "bt_codec_iso14230_view.h"



using namespace BTCore;
using namespace BTGui;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

CodecVisitor_ViewCreate::CodecVisitor_ViewCreate() :
    p_codec_view()
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

void CodecVisitor_ViewCreate::visit(Codec_ISO14230 &codec_iso14230)
{
    p_codec_view = std::make_shared<CodecISO14230View>(
            std::dynamic_pointer_cast<Codec_ISO14230>(
                codec_iso14230.getSharedPtr()
                )
            );
}

void CodecVisitor_ViewCreate::visit(CodecTransparent &codec_transparent)
{
    std::ignore = codec_transparent;
    p_codec_view = std::make_shared<CodecEmptyView>("Transparent");
}

std::shared_ptr<BTGui::CodecView> CodecVisitor_ViewCreate::getCodecView()
{
    return p_codec_view;
}


