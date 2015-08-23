/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_IODEV_VIEW_H
#define _BT_IODEV_VIEW_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>

#include "ui_bt_iodev_view.h"



namespace BTCore {
    class Project;
}

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTGui {
    class IODevView;
}

/**
 * TODO
 */
class BTGui::IODevView : public QObject
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    explicit IODevView(
            std::shared_ptr<BTCore::Project> p_project
            );


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    Ui::BTIODevView *p_iodev_view_ui;
    std::weak_ptr<BTCore::Project> wp_project;
    QWidget *p_iodev_sett_widg;
    bool opened;



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
    QWidget *getIODevSettWidget();



private:

    QWidget *createIODevSettWidget();
    void openedStatusApply();


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

private slots:

    void onIODevOpenStatusChanged(bool opened);

    void onWidgetDestroyed();

};


#endif // _BT_IODEV_VIEW_H
