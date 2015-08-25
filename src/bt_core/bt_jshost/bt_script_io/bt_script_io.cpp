/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_script_io.h"
#include "bt_project.h"
#include "bt_jshost.h"
#include "bt_bytearr_read_write.h"



using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ScriptIO::ScriptIO(
        std::shared_ptr<Project> p_project,
        std::shared_ptr<JSHost> p_jshost
        ) :
    wp_project(p_project),
    wp_jshost(p_jshost)
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

/**
 * Creates description to show to user: concatenates description
 * of script and description given to some particular call to
 * `writeEncoded()` or friends
 *
 * @param descr
 *      description provided to particular call to
 *      `writeEncoded()` or friends
 */
QString ScriptIO::createWriteDescr(QString descr)
{
    if (auto p_jshost = wp_jshost.lock()){
        QString cur_script_descr = p_jshost->getCurrentScriptDescr();

        if (descr.isEmpty()){
            descr = cur_script_descr;
        } else {
            descr = cur_script_descr + ": " + descr;
        }
    }

    return descr;
}



/* protected    */

/* public       */

ScriptIO *ScriptIO::writeEncoded(
        ByteArrReadWrite *p_bytearr,
        QString descr
        )
{
    if (auto p_project = wp_project.lock()){
        auto p_data = p_bytearr->getData();


        p_project->writeEncoded(
                *p_data,
                createWriteDescr(descr)
                );
    }

    return this;
}

ScriptIO *ScriptIO::writePlain(
        ByteArrReadWrite *p_bytearr,
        QString descr
        )
{
    if (auto p_project = wp_project.lock()){
        auto p_data = p_bytearr->getData();

        p_project->writePlain(
                *p_data,
                createWriteDescr(descr)
                );
    }

    return this;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


