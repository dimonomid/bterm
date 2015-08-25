/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_CORE_H
#define _BT_CORE_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/



/*******************************************************************************
 * NAMESPACE DECLARATION
 ******************************************************************************/

/**
 * Namespace `BTCore` contains everything related to Bot Terminal back-end
 * functionality. It doesn't contain any GUI (see `#BTGui`).
 */
namespace BTCore {

    /*******************************************************************************
     * TYPES
     ******************************************************************************/

    /**
     * Message level. Used by `#BTCore::EventSys` and `#BTCore::ScriptConsole`.
     */
    enum class MsgLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
    };


};


#endif // _BT_CORE_H
