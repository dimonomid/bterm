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

#include <QListWidget>
#include <QListWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "xmlsettings.h"

#include "htdatamsg.h"

#include "appl.h"

#include "my_util.h"

#include "htevent_data_raw.h"
#include "htevent_data_msg.h"
#include "htevent_sys.h"

#include "handler_view.h"

#include "mainwindow.h"
#include "qplaintextedit_my.h"



using namespace HTCore;
using namespace std;



/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

const QString MainWindow::WINDOW_TITLE = "HTerm";

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
    p_dw_handlers(new QDockWidget("Handlers")),
    handler_views(),
    need_to_restore_non_maximized_geometry(false)
{
    ui->setupUi(this);

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


#if 0
    {
        QDockWidget *p_dw;

        p_dw = new QDockWidget("dock");


        QListWidget *p_list = new QListWidget(this);

        p_dw->setWidget(p_list);

        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText("one");
            p_list->insertItem(0, newItem);
        }

        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText("two");
            p_list->insertItem(0, newItem);
        }

        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText("three");
            p_list->insertItem(0, newItem);
        }

        addDockWidget(Qt::TopDockWidgetArea, p_dw);
    }
#endif

#if 0
    {
        QWidget *p_widg = new QWidget();

        QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);



        p_widg->setLayout(p_lay);
    }
#endif


    connect(
            &appl, &Appl::eventDataRaw,
            this, &MainWindow::onNewDataRaw
           );

    connect(
            &appl, &Appl::eventDataMsg,
            this, &MainWindow::onNewDataMsg
           );

    connect(
            &appl, &Appl::eventSys,
            this, &MainWindow::onEventSys
           );

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

#if 0
void MainWindow::addHandlerEditWidget(
        std::shared_ptr<HTCore::ReqHandler> p_handler,
        QWidget *p_widg
        )
{
    QDockWidget *p_dw = new QDockWidget("Handler " + p_handler->getTitle());

    p_dw->setWidget(p_widg);

    addDockWidget(Qt::TopDockWidgetArea, p_dw);
}
#endif

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



/* private      */

void MainWindow::populateWithProject(std::shared_ptr<Project> p_project)
{
    QWidget *p_widg = new QWidget();

    QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);


    //-- iterate all handlers: 
    //   for each of them, create the view and display it:
    //   add a row in the handlers view, and create (hidden) dockwidget
    for (size_t i = 0; i < p_project->getHandlersCnt(); i++){

        //-- create view
        auto p_handler_view = make_shared<HandlerView>(*this, p_project->getHandler(i));

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


    p_widg->setLayout(p_lay);

    p_dw_handlers->setWidget(p_widg);
    p_dw_handlers->setObjectName("handlers_list");
}

void MainWindow::unpopulate()
{
    p_dw_handlers->setWidget(nullptr);

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

void MainWindow::initMainMenu()
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

#if 0
    p_act_show_debug = new QAction(tr("&Show debug events"), this);
    connect(
            p_act_show_debug, &QAction::triggered,
            this, &MainWindow::showDebugEventsToggle
           );

    p_act_show_debug->setCheckable(true);
    p_act_show_debug->setChecked(sys_msg_level == EventSys::Level::DEBUG);
#endif

    QMenu *menu_file = menuBar()->addMenu(tr("&File"));
    menu_file->addAction(p_act_open_project);
    menu_file->addAction(p_act_close_project);
    menu_file->addAction(p_act_save_project);
    menu_file->addAction(p_act_save_project_as);

#if 0
    QMenu *menu_opts = menuBar()->addMenu(tr("&Options"));
    menu_opts->addAction(p_act_show_debug);
#endif
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
    populateWithProject(p_project);

    setWindowTitle(
            WINDOW_TITLE + ": "
            + p_project->getTitle()
            + " ("
            + appl.getProjectFilename()
            + ")"
            );
    restoreProjectState();

    p_act_close_project->setEnabled(true);
}

void MainWindow::onProjectBeforeClose(std::shared_ptr<HTCore::Project> p_project)
{
    std::ignore = p_project;

    saveProjectState();

    setWindowTitle(WINDOW_TITLE);
    unpopulate();

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


void MainWindow::onNewDataRaw(std::shared_ptr<EventDataRaw> event_data_raw)
{
    QString text = MyUtil::byteArrayToHex(event_data_raw->getData()) + "<br>";

    //this->ui->pte_raw_data->appendHtmlNoNL(text, true);
    p_raw_data_pte->appendHtmlNoNL(text, true);

#if 0
    QTextCursor cursor = QTextCursor(this->ui->pte_raw_data->document());
    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml(text);
    cursor.movePosition(QTextCursor::End);
#endif
}

void MainWindow::onNewDataMsg(std::shared_ptr<EventDataMsg> event_data_msg)
{
    QString dir_text = "";
    QString handler_text = "";
    QString color = "black";

    switch (event_data_msg->getDir()){
        case EventDataMsg::Direction::TX:
            dir_text = "Tx";
            color = "blue";
            handler_text = " (" + event_data_msg->getHandler()->getTitle() + ")";
            break;
        case EventDataMsg::Direction::RX:
            dir_text = "Rx";
            break;
        default:
            //-- should never be here
            break;
    }

    QString text = "<font color='" + color + "'><b>msg " + dir_text + ":</b>" + handler_text + " " + MyUtil::byteArrayToHex(
            *event_data_msg->getMsg().getUserData()
            ) + "</font><br>";

    //this->ui->pte_messages->appendHtmlNoNL(text, true);
    this->p_log_pte->appendHtmlNoNL(text, true);


#if 0
    QTextCursor cursor = QTextCursor(this->ui->pte_messages->document());
    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml(text);
    cursor.movePosition(QTextCursor::End);
#endif
}

void MainWindow::onEventSys(std::shared_ptr<EventSys> p_event_sys)
{
    if (true/*event_sys.getLevel() >= mainwindow.sys_msg_level*/){
        QString html {};

        switch (p_event_sys->getLevel()){
            case EventSys::Level::DEBUG:
                html = "<font color='green'>" + p_event_sys->toString() + "</font>";
                break;
            case EventSys::Level::INFO:
                html = "<font color='blue'>" + p_event_sys->toString() + "</font>";
                break;
            case EventSys::Level::WARNING:
                html = "<font color='brown'>" + p_event_sys->toString() + "</font>";
                break;
            case EventSys::Level::ERROR:
                html = "<font color='red'>" + p_event_sys->toString() + "</font>";
                break;
        }

        this->p_log_pte->appendHtmlNoNL("* " + html + "<br>", true);
    }
}



