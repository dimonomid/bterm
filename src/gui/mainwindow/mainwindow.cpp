/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/


/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>
#include <QString>

#include <QAction>
#include <QSettings>
#include <QMenu>
#include <QSignalMapper>
#include <QDockWidget>
#include <QBoxLayout>
#include <QTimer>
#include <QFileDialog>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>

#include <QListWidget>
#include <QListWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bt_event_visitor__gui_handle.h"
#include "xmlsettings.h"

#include "bt_datamsg.h"

#include "appl.h"

#include "my_util.h"

#include "bt_event_data_raw.h"
#include "bt_event_data_msg.h"
#include "bt_event_sys.h"

#include "handler_view.h"

#include "mainwindow.h"
#include "qplaintextedit_my.h"
#include "bt_project_dialog.h"
#include "bt_project_view.h"

#include "bt_codec_visitor__view_create.h"
#include "bt_codec_view.h"


using namespace BTCore;
using namespace BTGui;
using namespace std;



/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const QString MainWindow::WINDOW_TITLE = "Bot Terminal";

const QString MainWindow::SETT_KEY__MAINWINDOW = "mainwindow";
const QString MainWindow::SETT_KEY__MAINWINDOW__GEOMETRY =
SETT_KEY__MAINWINDOW + "/geometry";
const QString MainWindow::SETT_KEY__MAINWINDOW__GEOMETRY_MAXIMIZED =
SETT_KEY__MAINWINDOW + "/geometry_maximized";
const QString MainWindow::SETT_KEY__MAINWINDOW__MAXIMIZED =
SETT_KEY__MAINWINDOW + "/maximized";
const QString MainWindow::SETT_KEY__MAINWINDOW__PROJ_STATE =
SETT_KEY__MAINWINDOW + "/proj_state";




/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

MainWindow::MainWindow(
        Appl &appl,
        QWidget *parent
        ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    appl(appl),
    windows_toggle_sigmap(this),
    p_raw_data_pte(new QPlainTextEdit_My(NULL)),
    p_log_pte(new QPlainTextEdit_My(NULL)),
    p_dw_raw_data(new QDockWidget("Raw data")),
    p_dw_handlers(new QDockWidget("Handlers list")),
    p_dw_project_sett(new QDockWidget("Project settings")),
    p_dw_codec_sett(new QDockWidget("Codec settings")),
    handler_views(),
    p_event_visitor__gui_handle(std::unique_ptr<EventVisitor_GuiHandle>(
                new EventVisitor_GuiHandle(*this)
                )),
    wp_project(),
    p_project_view(),
    p_codec_view(),
    need_to_restore_non_maximized_geometry(false)
{
    ui->setupUi(this);

    //TODO: configurable
    p_raw_data_pte->setMaximumBlockCount(1000);
    p_log_pte->setMaximumBlockCount(1000);

    //-- Enable for dock areas to contain arbitrary number of rows (horizontal
    //   or vertical). By default, when this option is false, dock areas can
    //   contain only a single row.
    this->setDockNestingEnabled(true);

    initSettings();
    initMainMenu();

    myRestoreState();

    //-- populate raw data dockwidget
    {
        QWidget *p_widg = new QWidget();
        QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);
        p_lay->addWidget(p_raw_data_pte);

        p_widg->setLayout(p_lay);
        p_dw_raw_data->setWidget(p_widg);
        p_dw_raw_data->setObjectName("raw_data");
    }

    //-- populate central widget (with log)
    {
        QWidget *p_widg = new QWidget();
        QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);
        p_lay->addWidget(p_log_pte);

        p_widg->setLayout(p_lay);
        setCentralWidget(p_widg);
    }

    addDockWidget(Qt::LeftDockWidgetArea, p_dw_raw_data);
    addDockWidget(Qt::TopDockWidgetArea, p_dw_handlers);
    addDockWidget(Qt::TopDockWidgetArea, p_dw_project_sett);
    addDockWidget(Qt::TopDockWidgetArea, p_dw_codec_sett);


    connect(&appl, &Appl::event, this, &MainWindow::onEvent);

    connect(&appl, &Appl::projectOpened, this, &MainWindow::onProjectOpened);

    connect(
            &appl, &Appl::projectBeforeClose,
            this, &MainWindow::onProjectBeforeClose
           );
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* public */

void MainWindow::showInRestoredState()
{
    auto p_sett = appl.settings();
    if (p_sett->value(SETT_KEY__MAINWINDOW__MAXIMIZED).toBool()){
        this->showMaximized();

        //-- because window is actually shown later (when the command
        //   is dispatched from the queue), we need to set flag
        //   not right now, but later.
        QTimer::singleShot(
                100 /* ms */,
                [this](){ need_to_restore_non_maximized_geometry = true; }
                );
    } else {
        show();
    }
}

bool MainWindow::event(QEvent *e)
{
    bool ret = QMainWindow::event(e);

    if (e->type() == QEvent::WindowStateChange){
        //-- window was just maximized or minimized.
        //   If it is minimized, then we should restore geometry that window
        //   had last time when it was minimized.
        //
        //   All this mess is needed because size of central widget (the log)
        //   is not saved as part of the state, and when we restore
        //   maximized window, we should set the geometry to occupy the whole
        //   screen.

        auto p_sett = appl.settings();
        if (!isMaximized() && need_to_restore_non_maximized_geometry){
            QRect rect = p_sett->value(SETT_KEY__MAINWINDOW__GEOMETRY).toRect();
            if (rect.width() != 0 && rect.height() != 0){
                setGeometry( rect );
            }
            need_to_restore_non_maximized_geometry = false;
        }

    }

    return ret;
}

void MainWindow::toggleCodecSettWindow()
{
    if (p_dw_codec_sett->isHidden()){
        p_dw_codec_sett->show();
    } else {
        p_dw_codec_sett->hide();
    }
}



/* private      */

void MainWindow::populateWithProject(std::shared_ptr<Project> p_project)
{
    QWidget *p_handlers_list_widg = new QWidget();

    QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);

    //-- add "add handler" button
    {
        QPushButton *p_add_handler_btn = new QPushButton("Add handler");
        p_lay->addWidget(p_add_handler_btn);
        connect(
                p_add_handler_btn, &QPushButton::clicked,
                this, &MainWindow::onAddHandlerButtonPressed
               );
    }


    //-- iterate all handlers: 
    //   for each of them, create the view and display it:
    //   add a row in the handlers view, and create (hidden) dockwidget
    for (size_t i = 0; i < p_project->getHandlersCnt(); i++){

        //-- create view
        auto p_handler_view = make_shared<HandlerView>(
                *this,
                p_project,
                p_project->getHandler(i)
                );

        //-- create row view
        QWidget *p_cur_widg = p_handler_view->getListItemWidget();
        p_lay->addWidget(p_cur_widg);

        //-- create and add hidden dockwidget
        {
            QDockWidget *p_dock = p_handler_view->getEditDockWidget();
            addDockWidget(Qt::TopDockWidgetArea, p_dock);
            p_dock->hide();
        }

        //-- store the handler in the vector
        handler_views.push_back(p_handler_view);
    }


    p_handlers_list_widg->setLayout(p_lay);

    QScrollArea *p_scroll_area = new QScrollArea();
    p_scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    p_scroll_area->setWidget(p_handlers_list_widg);
    p_scroll_area->setWidgetResizable(true);

    p_dw_handlers->setWidget(p_scroll_area);
    p_dw_handlers->setObjectName("handlers_list");


    //-- populate project settings window
    p_dw_project_sett->setWidget(p_project_view->getProjectSettWidget());
    p_dw_project_sett->setObjectName("project_sett");

    refreshCodecView(p_project);

    //-- subscribe on project's signals
    connect(
            p_project.get(), &Project::titleChanged,
            this, &MainWindow::onProjectTitleChanged
           );

    connect(
            p_project.get(), &Project::currentCodecNumChanged,
            this, &MainWindow::onProjectCodecNumChanged
           );
}

void MainWindow::unpopulate()
{
    p_dw_handlers->setWidget(nullptr);
    p_dw_project_sett->setWidget(nullptr);
    refreshCodecView(nullptr);

    qDebug("size: %d", handler_views.size());
    while (handler_views.size() > 0){
        std::shared_ptr<HandlerView> p_handler = handler_views.back();

        qDebug("remove");
        removeDockWidget(p_handler->getEditDockWidget());
        handler_views.pop_back();
    }
}

void MainWindow::initSettings()
{
    auto p_sett = appl.settings();
    p_sett->value(SETT_KEY__MAINWINDOW__GEOMETRY, QByteArray());
    p_sett->value(SETT_KEY__MAINWINDOW__GEOMETRY_MAXIMIZED, QByteArray());
    p_sett->value(SETT_KEY__MAINWINDOW__PROJ_STATE, QByteArray());
    p_sett->value(SETT_KEY__MAINWINDOW__MAXIMIZED, false);
}

void MainWindow::updateWindowTitle()
{
    if (auto p_project = wp_project.lock()){
        setWindowTitle(
                WINDOW_TITLE + ": "
                + p_project->getTitle()
                + " ("
                + appl.getProjectFilename()
                + ")"
                );
    } else {
        setWindowTitle(WINDOW_TITLE);
    }
}

void MainWindow::initMainMenu()
{
    //-- File menu {{{
    {
        p_act_open_project = new QAction(tr("&Open project"), this);
        connect(
                p_act_open_project, &QAction::triggered,
                this, &MainWindow::openProject
               );

        p_act_close_project = new QAction(tr("&Close project"), this);
        connect(
                p_act_close_project, &QAction::triggered,
                this, &MainWindow::closeProject
               );
        p_act_close_project->setEnabled(false);

        p_act_save_project = new QAction(tr("&Save project"), this);
        connect(
                p_act_save_project, &QAction::triggered,
                this, &MainWindow::saveProject
               );

        p_act_save_project_as = new QAction(tr("&Save project as ..."), this);
        connect(
                p_act_save_project_as, &QAction::triggered,
                this, &MainWindow::saveProjectAs
               );

        QMenu *menu_file = menuBar()->addMenu(tr("&File"));
        menu_file->addAction(p_act_open_project);
        menu_file->addAction(p_act_close_project);
        menu_file->addAction(p_act_save_project);
        menu_file->addAction(p_act_save_project_as);
    }
    // }}}

    //-- Project menu {{{
    {
        p_act_project_sett = new QAction(tr("&Project settings"), this);
        connect(
                p_act_project_sett, &QAction::triggered,
                this, &MainWindow::openProjectSettingsDialog
               );

        QMenu *menu_file = menuBar()->addMenu(tr("&Project"));
        menu_file->addAction(p_act_project_sett);
    }
    // }}}



}

void MainWindow::mySaveState()
{
    auto p_sett = appl.settings();
    if (!this->isMaximized()){
        p_sett->setValue(SETT_KEY__MAINWINDOW__GEOMETRY, this->geometry());
        p_sett->setValue(SETT_KEY__MAINWINDOW__MAXIMIZED, false);
    } else {
        p_sett->setValue(SETT_KEY__MAINWINDOW__GEOMETRY_MAXIMIZED, this->geometry());
        p_sett->setValue(SETT_KEY__MAINWINDOW__MAXIMIZED, true);
    }
}

void MainWindow::myRestoreState()
{
    auto p_sett = appl.settings();

    QString geometry_key = SETT_KEY__MAINWINDOW__GEOMETRY;
    if (p_sett->value(SETT_KEY__MAINWINDOW__MAXIMIZED).toBool()){
        geometry_key = SETT_KEY__MAINWINDOW__GEOMETRY_MAXIMIZED;
    }

    QRect rect = p_sett->value(geometry_key).toRect();
    if (rect.width() != 0 && rect.height() != 0){
        setGeometry( rect );
    }
}

void MainWindow::saveProjectState()
{
    auto p_sett = appl.settings();
    QString proj_filename = appl.getProjectFilename();

    if (!proj_filename.isEmpty()){
        p_sett->setValue(
                SETT_KEY__MAINWINDOW__PROJ_STATE + "/" + getTagnameFromFilename(proj_filename),
                this->saveState()
                );
    }
}

void MainWindow::restoreProjectState()
{
    auto p_sett = appl.settings();
    QString proj_filename = appl.getProjectFilename();

    if (!proj_filename.isEmpty()){
        QByteArray proj_state = p_sett->value(
                SETT_KEY__MAINWINDOW__PROJ_STATE + "/" + getTagnameFromFilename(proj_filename)
                ).toByteArray();

        restoreState(proj_state);

    }
}

/**
 * Refresh handlers list
 */
void MainWindow::refreshHandlersList()
{
    if (auto p_project = wp_project.lock()){
        saveProjectState();
        unpopulate();
        populateWithProject(p_project);
        restoreProjectState();

        scrollAllToBottom();
    }
}

void MainWindow::refreshCodecView(std::shared_ptr<Project> p_project)
{
    if (p_project != nullptr){
        CodecVisitor_ViewCreate codec_visitor__view_create {};
        p_project->getCodec()->accept(codec_visitor__view_create);

        p_codec_view = codec_visitor__view_create.getCodecView();

        //-- populate codec settings window
        p_dw_codec_sett->setWidget(p_codec_view->getCodecSettWidget());
        p_dw_codec_sett->setObjectName("codec_sett");
    } else {
        p_dw_codec_sett->setWidget(nullptr);
    }
}

void MainWindow::scrollAllToBottom()
{
    p_log_pte->verticalScrollBar()->setValue(
            p_log_pte->verticalScrollBar()->maximum()
            );

    p_raw_data_pte->verticalScrollBar()->setValue(
            p_raw_data_pte->verticalScrollBar()->maximum()
            );
}

QString MainWindow::getTagnameFromFilename(QString filename)
{
    QRegularExpression re {"[^a-zA-Z0-9_]"};
    return filename.replace(re, "_");
}


void MainWindow::closeEvent(QCloseEvent *p_event)
{
    mySaveState();
    saveProjectState();

    QMainWindow::closeEvent(p_event);
}





/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* public       */

/* protected    */

/* private      */

void MainWindow::onProjectOpened(std::shared_ptr<Project> p_project)
{
    p_project_view = std::make_shared<ProjectView>(p_project, *this);

    populateWithProject(p_project);

    restoreProjectState();

    p_act_close_project->setEnabled(true);

    //-- subscribe for project's signals
    connect(
            p_project.get(), &Project::reqHandlerAdded,
            this, &MainWindow::onReqHandlerAdded
           );

    connect(
            p_project.get(), &Project::reqHandlerRemoved,
            this, &MainWindow::onReqHandlerRemoved
           );
    connect(
            p_project.get(), &Project::reqHandlersReordered,
            this, &MainWindow::onReqHandlersReordered
           );

    //-- store weak pointer to the project
    this->wp_project = std::weak_ptr<BTCore::Project>(p_project);

    updateWindowTitle();
    scrollAllToBottom();
}

void MainWindow::onProjectBeforeClose(std::shared_ptr<Project> p_project)
{
    std::ignore = p_project;

    saveProjectState();

    unpopulate();

    this->wp_project = std::weak_ptr<BTCore::Project>();
    p_project_view = nullptr;

    updateWindowTitle();

    p_act_close_project->setEnabled(false);
}

void MainWindow::openProject()
{
    //-- get filename
    QString wanted_filename = QFileDialog::getOpenFileName(
            this,
            QObject::tr("Open device protocol file"),
            appl.getLastProjectFilename(),
            "Xml files (*.xml)"
            );

    if (!wanted_filename.isEmpty()){
        if (QFile::exists(wanted_filename)){
            appl.openProject(wanted_filename);
        }
    }

}

void MainWindow::saveProject()
{
    //-- if we already have project filename, then save it.
    //   Otherwise, ask user for the filename
    if (!appl.getProjectFilename().isEmpty()){
        appl.saveProject();
    } else {
        saveProjectAs();
    }
}

void MainWindow::saveProjectAs()
{
    //-- get filename
    QString wanted_filename = QFileDialog::getSaveFileName(
            this,
            QObject::tr("Save device protocol file"),
            appl.getLastProjectFilename(),
            "Xml files (*.xml)"
            );

    if (!wanted_filename.isEmpty()){
        appl.saveProject(wanted_filename);
    }

}

void MainWindow::closeProject()
{
    appl.closeProject();
}

void MainWindow::openProjectSettingsDialog()
{
    if (auto p_project = wp_project.lock()){
        BTProjectDialog *p_dialog = new BTProjectDialog(
                p_project,
                this
                );
        p_dialog->setAttribute(Qt::WA_DeleteOnClose);

        p_dialog->exec();
        qDebug("done");
    }
}


void MainWindow::onEvent(std::shared_ptr<Event> p_event)
{
    //-- handle event with visitor
    p_event->accept(*p_event_visitor__gui_handle);
}

void MainWindow::onAddHandlerButtonPressed()
{
    //-- add new handler
    if (auto p_project = wp_project.lock()){
        p_project->addHandler(std::make_shared<ReqHandler>());
    }
}

void MainWindow::onProjectTitleChanged(const QString &title)
{
    std::ignore = title;
    updateWindowTitle();
}

void MainWindow::onProjectCodecNumChanged(std::shared_ptr<Codec> p_codec)
{
    std::ignore = p_codec;
    if (auto p_project = wp_project.lock()){
        refreshCodecView(p_project);
    }
}

void MainWindow::onReqHandlerAdded(
        std::shared_ptr<ReqHandler> p_handler,
        size_t index
        )
{
    std::ignore = p_handler;
    std::ignore = index;

    refreshHandlersList();
}

void MainWindow::onReqHandlerRemoved(
        std::shared_ptr<ReqHandler> p_handler,
        size_t index
        )
{
    std::ignore = p_handler;
    std::ignore = index;

    refreshHandlersList();
}

void MainWindow::onReqHandlersReordered()
{
    refreshHandlersList();
}


