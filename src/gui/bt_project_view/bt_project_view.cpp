/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDockWidget>

#include "bt_project_view.h"
#include "bt_project.h"


using namespace BTGui;
using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ProjectView::ProjectView(
        std::shared_ptr<Project> p_project
        ) :
    p_project_view_ui(new Ui::BTProjectView),
    wp_project(std::weak_ptr<Project>(p_project)),
    p_project_edit_widg()
{
#if 0
    QWidget *p_project_edit_widg = createProjectEditWidget();
    p_dock = std::make_shared<QDockWidget>("Project edit");
    p_dock->setObjectName("project_edit");
    p_dock->setWidget(p_project_edit_widg);
#endif
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

QWidget *ProjectView::createProjectEditWidget()
{
    QWidget *p_widg = new QWidget();

    if (auto p_project = wp_project.lock()){
        p_project_view_ui->setupUi(p_widg);

        p_project_view_ui->proj_title_edit->setText(
                p_project->getTitle()
                );

        connect(
                p_project_view_ui->proj_title_edit, &QLineEdit::textChanged,
                this, &ProjectView::onTitleChangedByUser
               );

        connect(
                p_widg, &QObject::destroyed,
                this, &ProjectView::onWidgetDestroyed
               );
    }

    return p_widg;
}


/* protected    */

/* public       */

QWidget *ProjectView::getProjectEditWidget()
{
    if (p_project_edit_widg == nullptr){
        p_project_edit_widg = createProjectEditWidget();
    }

    return p_project_edit_widg;
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void ProjectView::onTitleChangedByUser(const QString &text)
{
    if (auto p_project = wp_project.lock()){
        p_project->setTitle(text);
    }
}

void ProjectView::onWidgetDestroyed()
{
    p_project_edit_widg = nullptr;
}

/* protected    */

/* public       */


