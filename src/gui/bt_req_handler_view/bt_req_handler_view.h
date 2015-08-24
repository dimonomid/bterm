/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_REQ_HANDLER_VIEW_H
#define _BT_REQ_HANDLER_VIEW_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>
#include <memory>



namespace BTCore {
    class Project;
    class ReqHandler;
}


class MainWindow;
class QDockWidget;
class QLabel;
class QPlainTextEdit;

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTGui {
    class ReqHandlerView;
}

/**
 * Class that represents GUI view for `#BTCore::ReqHandler`.
 * It contains both views for:
 *
 * - Single row in the handlers list
 * - Dock widget with handler edit form
 */
class BTGui::ReqHandlerView : public QObject
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    ReqHandlerView(
            MainWindow &mainwindow,
            std::shared_ptr<BTCore::Project> p_project,
            std::shared_ptr<BTCore::ReqHandler> p_handler
            );


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    MainWindow &mainwindow;
    std::shared_ptr<BTCore::ReqHandler> p_handler;

    //-- NOTE: we use shared_ptr here instead of raw pointers, because
    //   docs say that when we remove dockwidget from mainwindow by calling
    //   removeDockWidget(), the dockwidget is NOT deleted (unlike other GUI
    //   stuff in Qt). So, let the lifetime to be managed by shared_ptr, then.
    //
    //   It is created just when the instance of ReqHandlerView is created,
    //   for the same reason: Qt doesn't delete it.
    std::shared_ptr<QDockWidget> p_dock;

    QWidget *p_list_item_widget;
    QLabel *p_list_item_label_name;
    QPlainTextEdit *p_script_edit;
    std::weak_ptr<BTCore::Project> wp_project;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * NOTE: each time this function is called, the same DockWidget
     * is returned, but the caller is NOT responsible to delete it:
     * since Qt doesn't delete `DockWidget`s automatically when we
     * call `removeDockWidget()`, this class takes care of it.
     *
     * So, when you delete the instance of this clas
     * (`ReqHandlerView`), the dockwidget gets deleted as well.
     */
    QDockWidget *getEditDockWidget() const;

    /**
     * NOTE: each time this function is called, the same widget is returned,
     * and the caller is responsible to delete it eventually.
     *
     * Widget will be actually created at the first call, so if this method
     * never called, then widget is not created at all.
     */
    QWidget *getListItemWidget();



private:

    QWidget *createEditWidget();
    QWidget *createListItemWidget();

    QString getEditDockWidgetTitle() const;
    QString getListItemWidgetTitle() const;



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

private slots:

    void onEditButtonPressed();
    void onRemoveButtonPressed();
    void onUpButtonPressed();
    void onDownButtonPressed();
    void onTitleChangedByUser(const QString &text);
    void onScriptChangedByUser();
    void onReqHandlerTitleChanged(const QString &text);
    void onListItemWidgetDestroyed();



};


#endif // _BT_REQ_HANDLER_VIEW_H
