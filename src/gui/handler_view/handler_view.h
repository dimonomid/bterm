/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HANDLER_VIEW_H
#define _HANDLER_VIEW_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>



namespace HTCore {
    class ReqHandler;
}

class MainWindow;
class QDockWidget;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

/**
 * TODO
 */
class HandlerView : public QObject
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    HandlerView(
            MainWindow &mainwindow,
            std::shared_ptr<HTCore::ReqHandler> p_handler
            );


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    MainWindow &mainwindow;
    std::shared_ptr<HTCore::ReqHandler> p_handler;

    //-- NOTE: we use shared_ptr here instead of raw pointers, because
    //   docs say that when we remove dockwidget from mainwindow by calling
    //   removeDockWidget(), the dockwidget is NOT deleted (unlike other GUI
    //   stuff in Qt). So, let the lifetime to be managed by shared_ptr, then.
    //
    //   It is created just when the instance of HandlerView is created,
    //   for the same reason: Qt doesn't delete it.
    std::shared_ptr<QDockWidget> p_dock;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * NOTE: each time this function is called, new widget is created, and the
     * caller is responsible to delete it eventually.
     *
     * Usually it is done just by adding widget to some other widget as a child,
     * so that Qt will take care of all this.
     *
     * We don't
     */
    QWidget *createListItemWidget() const;
    QDockWidget *getEditDockWidget() const;



private:

    QWidget *createEditWidget() const;



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

private slots:

    void onEditButtonPressed();



};


#endif // _HANDLER_VIEW_H
