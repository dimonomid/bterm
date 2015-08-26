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
public:

    /**
     * The struct represents a set of widgets that are used as a row in
     * handlers list.
     */
    struct ListRowWidgets {
        QWidget *p_handler_title;
        QWidget *p_edit_btn;
        QWidget *p_up_btn;
        QWidget *p_down_btn;
        QWidget *p_del_btn;

        ListRowWidgets() :
            p_handler_title(),
            p_edit_btn(),
            p_up_btn(),
            p_down_btn(),
            p_del_btn()
        {
        }
    };


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

    std::shared_ptr<ListRowWidgets> p_list_row;
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
     * NOTE: each time this function is called, shared pointer to the same
     * structure is returned, with the same pointers to widgets. And the caller
     * is responsible for deletion of all of these widgets.
     *
     * Structure (and widgets) will be actually created at the first call, so
     * if this method never called, then widgets are not created at all.
     */
    std::shared_ptr<ListRowWidgets> getListRow();


private:

    QWidget *createEditWidget();
    std::shared_ptr<ListRowWidgets> createListRow();

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



};


#endif // _BT_REQ_HANDLER_VIEW_H
