/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/


/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QString>

#include <QAction>
#include <QSettings>
#include <QMenu>
#include <QSignalMapper>
#include <QDockWidget>
#include <QBoxLayout>

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

#include "handler_view.h"

#include "mainwindow.h"
#include "qplaintextedit_my.h"



using namespace HTCore;
using namespace std;



/*******************************************************************************
 * STATIC DATA
 ******************************************************************************/

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
   handler_views()
{
   ui->setupUi(this);

   //-- Enable for dock areas to contain arbitrary number of rows (horizontal
   //   or vertical). By default, when this option is false, dock areas can
   //   contain only a single row.
   this->setDockNestingEnabled(true);

   initSettings();

   myRestoreState();

   //-- populate raw data dockwidget
   {
      QWidget *p_widg = new QWidget();
      QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);
      p_lay->addWidget(p_raw_data_pte);

      p_widg->setLayout(p_lay);
      p_dw_raw_data->setWidget(p_widg);
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

   connect(&appl, &Appl::projectOpened, this, &MainWindow::onProjectOpened);
}

MainWindow::~MainWindow()
{
   delete ui;
}


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* public */

void MainWindow::addHandlerEditWidget(
      std::shared_ptr<HTCore::ReqHandler> p_handler,
      QWidget *p_widg
      )
{
   QDockWidget *p_dw = new QDockWidget("Handler " + p_handler->getName());

   p_dw->setWidget(p_widg);

   addDockWidget(Qt::TopDockWidgetArea, p_dw);
}



/* private      */

void MainWindow::populateWithProject(std::shared_ptr<Project> p_project)
{
   QWidget *p_widg = new QWidget();

   QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);


   for (size_t i = 0; i < p_project->getHandlersCnt(); i++){

      auto p_handler_view = make_shared<HandlerView>(*this, p_project->getHandler(i));
      QWidget *p_cur_widg = p_handler_view->createListItemWidget();

      p_lay->addWidget(p_cur_widg);

      handler_views.push_back(p_handler_view);
   }



   p_widg->setLayout(p_lay);

   p_dw_handlers->setWidget(p_widg);
}

void MainWindow::initSettings()
{
   auto p_sett = appl.settings();
   p_sett->value(SETT_KEY__MAINWINDOW__GEOMETRY, QByteArray());
   p_sett->value(SETT_KEY__MAINWINDOW__GEOMETRY_MAXIMIZED, QByteArray());
   p_sett->value(SETT_KEY__MAINWINDOW__PROJ_STATE, QByteArray());
   p_sett->value(SETT_KEY__MAINWINDOW__MAXIMIZED, false);
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

   restoreProjectState();
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
   QString color = "black";

   switch (event_data_msg->getDir()){
      case EventDataMsg::Direction::TX:
         dir_text = "Tx";
         color = "blue";
         break;
      case EventDataMsg::Direction::RX:
         dir_text = "Rx";
         break;
      default:
         //-- should never be here
         break;
   }

   QString text = "<font color='" + color + "'><b>msg " + dir_text + ":</b> " + MyUtil::byteArrayToHex(
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




