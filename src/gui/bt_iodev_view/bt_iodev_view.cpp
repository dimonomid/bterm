/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_iodev_view.h"

#include "bt_iodev.h"
#include "bt_project.h"



using namespace BTGui;
using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

IODevView::IODevView(
        std::shared_ptr<Project> p_project
        ) :
    p_iodev_view_ui(new Ui::BTIODevView),
    wp_project(std::weak_ptr<Project>(p_project)),
    p_iodev_sett_widg()
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

QWidget *IODevView::getIODevSettWidget()
{
    if (p_iodev_sett_widg == nullptr){
        p_iodev_sett_widg = createIODevSettWidget();
    }

    return p_iodev_sett_widg;
}


QWidget *IODevView::createIODevSettWidget()
{
    QWidget *p_widg = new QWidget();

    if (auto p_project = wp_project.lock()){
        p_iodev_view_ui->setupUi(p_widg);

        std::shared_ptr<IODev> p_iodev = p_project->getIODev();

        p_iodev_view_ui->baudrate->setValue(
                p_iodev->getBaudRate()
                );
    }

    return p_widg;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


