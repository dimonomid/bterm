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
    class Codec;
}

namespace BTGui {
    class ProjectView;
    class CodecView;
    class IODevView;
    class ReqHandlerView;
}

namespace Ui {
    class MainWindow;
}

class Appl;
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
    QDockWidget      *p_dw_project_sett;
    QDockWidget      *p_dw_codec_sett;
    QDockWidget      *p_dw_iodev_sett;

    QAction *p_act_new_project;
    QAction *p_act_open_project;
    QAction *p_act_close_project;
    QAction *p_act_save_project;
    QAction *p_act_save_project_as;

    QAction *p_act_project_sett;


    std::vector<std::shared_ptr<BTGui::ReqHandlerView>> handler_views;

    std::unique_ptr<EventVisitor_GuiHandle> p_event_visitor__gui_handle;

    std::weak_ptr<BTCore::Project> wp_project;
    std::shared_ptr<BTGui::ProjectView> p_project_view;
    std::shared_ptr<BTGui::IODevView> p_iodev_view;
    std::shared_ptr<BTGui::CodecView> p_codec_view;


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

    /**
     * if last state was maximized, then calls `showMaximized()`,
     * otherwise, calls `show()`.
     */
    void showInRestoredState();

    /**
     * We have to override this method in order to save/restore state
     * correctly. See some details in comments inside this function.
     */
    bool event(QEvent *e) override;

    /**
     * If codec settings window is opened, then hides it, otherwise, shows it.
     * This function is needed because project settings window contains
     * drop-down menu with codecs, and it's convenient to have a button "Settings"
     * near this drop-down menu.
     */
    void toggleCodecSettWindow();


private:

    void populateWithProject(std::shared_ptr<BTCore::Project> p_project);
    void unpopulate();

    void updateWindowTitle();
    void initMainMenu();
    void initSettings();

    void mySaveState();
    void myRestoreState();

    void saveProjectState();
    void restoreProjectState();

    void refreshHandlersList();
    void refreshCodecView(std::shared_ptr<BTCore::Project> p_project);

    void scrollAllToBottom();

    QString getTagnameFromFilename(QString filename);

private:
    void closeEvent(QCloseEvent *p_event) override;




    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

private slots:

    void onProjectOpened(QString proj_filename, std::shared_ptr<BTCore::Project> p_project);
    void onProjectSaved(QString proj_filename, std::shared_ptr<BTCore::Project> p_project);
    void onProjectBeforeClose(std::shared_ptr<BTCore::Project> p_project);

    void onEvent(std::shared_ptr<BTCore::Event> p_event);

    void newProject();
    void openProject();
    void closeProject();
    void saveProject();
    void saveProjectAs();

    void onAddHandlerButtonPressed();

    void onProjectTitleChanged(const QString &title);
    void onProjectCodecNumChanged(std::shared_ptr<BTCore::Codec> p_codec);

    void onReqHandlerAdded(
            std::shared_ptr<BTCore::ReqHandler> p_handler,
            size_t index
            );
    void onReqHandlerRemoved(
            std::shared_ptr<BTCore::ReqHandler> p_handler,
            size_t index
            );
    void onReqHandlersReordered();
};

#endif // MAINWINDOW_H
