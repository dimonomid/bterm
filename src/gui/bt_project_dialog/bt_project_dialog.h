/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_PROJECT_DIALOG_H
#define _BT_PROJECT_DIALOG_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>

#include "ui_bt_project_dialog.h"



namespace Ui {
    class BTProjectDialog;
}

namespace BTCore {
    class Project;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

/**
 * TODO
 */
class BTProjectDialog : public QDialog
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:

    explicit BTProjectDialog(
            std::shared_ptr<BTCore::Project> p_project,
            QWidget *p_parent = nullptr,
            Qt::WindowFlags flags = 0
            );



   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

    Ui::BTProjectDialog *p_ui;
    std::shared_ptr<BTCore::Project> p_project;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/

   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/

};


#endif // _BT_PROJECT_DIALOG_H
