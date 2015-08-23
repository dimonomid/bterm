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
    QWidget *p_project_sett_widg;
    MainWindow &mainwindow;


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
    QWidget *getProjectSettWidget();



private:

    QWidget *createProjectSettWidget();


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
