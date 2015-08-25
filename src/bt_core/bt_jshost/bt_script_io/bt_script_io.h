/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_SCRIPT_IO_H
#define _BT_SCRIPT_IO_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>



namespace BTCore {
    class Project;
    class JSHost;
}


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class ScriptIO;
    class ByteArrReadWrite;
}


/**
 * TODO
 */
class BTCore::ScriptIO : public QObject
{
Q_OBJECT

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    explicit ScriptIO(
            std::shared_ptr<Project> p_project,
            std::shared_ptr<JSHost> p_jshost
            );


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- weak pointer to Project that was given to constructor
    std::weak_ptr<Project> wp_project;

    //-- weak pointer to JSHost that was given to constructor
    std::weak_ptr<JSHost> wp_jshost;



    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    Q_INVOKABLE BTCore::ScriptIO *writeEncoded(
            BTCore::ByteArrReadWrite *p_bytearr,
            QString descr = ""
            );

    Q_INVOKABLE BTCore::ScriptIO *writePlain(
            BTCore::ByteArrReadWrite *p_bytearr,
            QString descr = ""
            );




private:

    QString createWriteDescr(QString descr);


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BT_SCRIPT_IO_H
