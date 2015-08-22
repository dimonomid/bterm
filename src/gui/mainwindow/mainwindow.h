/******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <vector>
#include <memory>
#include <cstdint>

#include <QMainWindow>
#include <QSignalMapper>


namespace BTCore {
    class Event;
    class Project;
    class ReqHandler;
}

namespace Ui {
    class MainWindow;
}

class Appl;
class HandlerView;
class QPlainTextEdit_My;
class EventVisitor_GuiHandle;



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

/**
 * Class that represents main application window. It listens for events from
 * `#Appl` and behaves accordingly.
 */
class MainWindow : public QMainWindow
{
Q_OBJECT

    friend EventVisitor_GuiHandle;

    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    explicit MainWindow(
            Appl &appl,
            QWidget *parent = 0
            );
    ~MainWindow();



    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/

private:
    Ui::MainWindow   *ui;
    Appl &appl;

    QSignalMapper     windows_toggle_sigmap;

    QAction          *p_act_raw_data;
    QAction          *p_act_messages;


    QPlainTextEdit_My   *p_raw_data_pte;
    QPlainTextEdit_My   *p_log_pte;

    QDockWidget      *p_dw_raw_data;
    QDockWidget      *p_dw_handlers;

    QAction *p_act_open_project;
    QAction *p_act_close_project;
    QAction *p_act_save_project;
    QAction *p_act_save_project_as;

    //-- NOTE: we use shared_ptr here instead of raw pointers, because
    //   docs say that when we remove dockwidget from mainwindow by calling
    //   removeDockWidget(), the dockwidget is NOT deleted (unlike other GUI
    //   stuff in Qt). So, let the lifetime to be managed by shared_ptr, then.
    std::list<std::shared_ptr<QDockWidget>>   handler_docks;


    std::vector<std::shared_ptr<HandlerView>> handler_views;

    std::unique_ptr<EventVisitor_GuiHandle> p_event_visitor__gui_handle;


    //-- A hack that is needed for the case when application was closed in
    //   maximized state. When it is reopened, in order for central widget
    //   to have the same geometry as it had before, we need to set geometry
    //   of window for the whole screen. But, when window is unmaximized,
    //   we need to restore actual non-maximized geometry.
    //
    //   See usage in mainwindow.cpp
    bool need_to_restore_non_maximized_geometry;


    static const QString WINDOW_TITLE;

    static const QString SETT_KEY__MAINWINDOW;
    static const QString SETT_KEY__MAINWINDOW__GEOMETRY;
    static const QString SETT_KEY__MAINWINDOW__GEOMETRY_MAXIMIZED;
    static const QString SETT_KEY__MAINWINDOW__MAXIMIZED;
    static const QString SETT_KEY__MAINWINDOW__PROJ_STATE;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/

public:

#if 0
    void addHandlerEditWidget(
            std::shared_ptr<BTCore::ReqHandler> p_handler,
            QWidget *p_widg
            );
#endif

    /**
     * if last state was maximized, then calls `showMaximized()`,
     * otherwise, calls `show()`.
     */
    void showInRestoredState();
    bool event(QEvent *e) override;


private:

    void populateWithProject(std::shared_ptr<BTCore::Project> p_project);
    void unpopulate();

    void initMainMenu();
    void initSettings();

    void mySaveState();
    void myRestoreState();

    void saveProjectState();
    void restoreProjectState();

    QString getTagnameFromFilename(QString filename);

private:
    void closeEvent(QCloseEvent *p_event) override;




    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

private slots:

    void onProjectOpened(std::shared_ptr<BTCore::Project> p_project);
    void onProjectBeforeClose(std::shared_ptr<BTCore::Project> p_project);

    void onEvent(std::shared_ptr<BTCore::Event> p_event);

    void openProject();
    void closeProject();
    void saveProject();
    void saveProjectAs();

};

#endif // MAINWINDOW_H
