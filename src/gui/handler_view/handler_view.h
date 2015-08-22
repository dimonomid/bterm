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
class QLabel;
class QPlainTextEdit;

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

    QWidget *p_list_item_widget;
    QLabel *p_list_item_label_name;
    QPlainTextEdit *p_script_edit;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    QDockWidget *getEditDockWidget() const;
    QWidget *getListItemWidget();



private:

    QWidget *createEditWidget();
    /**
     * NOTE: each time this function is called, the same widget is returned,
     * and the caller is responsible to delete it eventually.
     *
     * Widget will be actually created at the first call, so if this method
     * never called, then widget is not created at all.
     */
    QWidget *createListItemWidget();
    //void applyReqName();

    QString getEditDockWidgetTitle() const;
    QString getListItemWidgetTitle() const;



    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

private slots:

    void onEditButtonPressed();
    void onTitleChangedByUser(const QString &text);
    void onScriptChangedByUser();
    void onReqHandlerTitleChanged(const QString &text);



};


#endif // _HANDLER_VIEW_H
