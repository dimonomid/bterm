/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_PROJECT_VIEW_H
#define _BT_PROJECT_VIEW_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>

#include "ui_bt_project_view.h"



class QDockWidget;
class MainWindow;

namespace BTCore {
    class Project;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTGui {
    class ProjectView;
}

/**
 * TODO
 */
class BTGui::ProjectView : public QObject
{
   /****************************************************************************
    * TYPES
    ***************************************************************************/

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
    explicit ProjectView(
            std::shared_ptr<BTCore::Project> p_project,
            MainWindow &mainwindow
            );

   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
private:

    Ui::BTProjectView *p_project_view_ui;
    std::weak_ptr<BTCore::Project> wp_project;
    QWidget *p_project_edit_widg;
    MainWindow &mainwindow;


   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/
public:

    QWidget *getProjectSettWidget();



private:

    QWidget *createProjectEditWidget();


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/

private slots:

    void onTitleChangedByUser(const QString &text);
    void onCodecSelectionChangedByUser(int index);
    void onWidgetDestroyed();
    void toggleCodecSettWindow();


};


#endif // _BT_PROJECT_VIEW_H
