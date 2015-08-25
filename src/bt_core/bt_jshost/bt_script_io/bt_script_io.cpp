/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_script_io.h"
#include "bt_project.h"
#include "bt_bytearr_read_write.h"



using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ScriptIO::ScriptIO(
        std::shared_ptr<Project> p_project
        ) :
    wp_project(p_project)
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

ScriptIO *ScriptIO::writeEncoded(
        ByteArrReadWrite *p_bytearr
        )
{
    if (auto p_project = wp_project.lock()){
        qDebug("write called");

        auto p_data = p_bytearr->getData();

        p_project->writeEncoded(
                *p_data,
                "sdf"//TODO: JSHost::getCurrentScriptDescr
                );
    }

    return this;
}

ScriptIO *ScriptIO::writePlain(
        ByteArrReadWrite *p_bytearr
        )
{
    if (auto p_project = wp_project.lock()){
        qDebug("writePlain called");
    }

    return this;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


