
#include <QString>

#include <QAction>
#include <QSettings>
#include <QMenu>
#include <QSignalMapper>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "htdatamsg.h"

#include "appl.h"

#include "my_util.h"

#include "htevent_data_raw.h"
#include "htevent_data_msg.h"

#include "mainwindow.h"

using namespace HTCore;


MainWindow::MainWindow(
      Appl &appl,
      QWidget *parent
      ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    appl(appl),
    windows_toggle_sigmap(this)
{
    ui->setupUi(this);

    //-- test save/restore state
    {
       QAction *saveStateAction = new QAction(tr("&Save State"), this);
       connect(saveStateAction, &QAction::triggered, this, &MainWindow::mySaveState);

       QAction *restoreStateAction = new QAction(tr("&Restore State"), this);
       connect(restoreStateAction, &QAction::triggered, this, &MainWindow::myRestoreState);

       QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
       fileMenu->addAction(saveStateAction);
       fileMenu->addAction(restoreStateAction);
    }


    //-- init toolbars menu {{{
    {

       connect(
             &this->windows_toggle_sigmap,
             static_cast<void (QSignalMapper::*)(QWidget *)>(
                &QSignalMapper::mapped
                ),
             this, &MainWindow::toolbarToggle
             );

       QMenu *p_toolbars = menuBar()->addMenu(tr("&Toolbars"));

       //-- init "raw data" menuitem
       {
          p_act_raw_data = new QAction(tr("&Raw data"), this);
          p_act_raw_data->setCheckable(true);
          connect(
                p_act_raw_data, &QAction::triggered,
                &this->windows_toggle_sigmap, 
                static_cast<void (QSignalMapper::*)()>(
                   &QSignalMapper::map
                   )
                );
          this->windows_toggle_sigmap.setMapping(p_act_raw_data, this->ui->dockwidg_raw_data);
          p_toolbars->addAction(p_act_raw_data);

          connect(
                this->ui->dockwidg_raw_data, &QDockWidget::visibilityChanged,
                this, &MainWindow::windowVisChanged
                );

       }

       //-- init "messages" menuitem
       {
          p_act_messages = new QAction(tr("&Messages"), this);
          p_act_messages->setCheckable(true);
          connect(
                p_act_messages, &QAction::triggered,
                &this->windows_toggle_sigmap,
                static_cast<void (QSignalMapper::*)()>(
                   &QSignalMapper::map
                   )
                );
          this->windows_toggle_sigmap.setMapping(p_act_messages, this->ui->dockwidg_messages);
          p_toolbars->addAction(p_act_messages);

          connect(
                this->ui->dockwidg_messages, &QDockWidget::visibilityChanged,
                this, &MainWindow::windowVisChanged
                );

       }

    }
    // }}}

    connect(
          &appl, &Appl::eventDataRaw,
          this, &MainWindow::onNewDataRaw
          );

    connect(
          &appl, &Appl::eventDataMsg,
          this, &MainWindow::onNewDataMsg
          );
}

MainWindow::~MainWindow()
{
    delete ui;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void MainWindow::onNewDataRaw(std::shared_ptr<EventDataRaw> event_data_raw)
{
   QString text = MyUtil::byteArrayToHex(event_data_raw->getData()) + "<br>";

   this->ui->pte_raw_data->appendHtmlNoNL(text, true);

#if 0
   QTextCursor cursor = QTextCursor(this->ui->pte_raw_data->document());
   cursor.movePosition(QTextCursor::End);
   cursor.insertHtml(text);
   cursor.movePosition(QTextCursor::End);
#endif
}

void MainWindow::onNewDataMsg(std::shared_ptr<EventDataMsg> event_data_msg)
{
   QString text = "<b>msg: </b>" + MyUtil::byteArrayToHex(event_data_msg->getMsg().getUserData()) + "<br>";

   this->ui->pte_messages->appendHtmlNoNL(text, true);


#if 0
   QTextCursor cursor = QTextCursor(this->ui->pte_messages->document());
   cursor.movePosition(QTextCursor::End);
   cursor.insertHtml(text);
   cursor.movePosition(QTextCursor::End);
#endif
}

void MainWindow::toolbarToggle(QWidget *p_widget)
{
   QDockWidget *p_dockwidget = dynamic_cast<QDockWidget *>(p_widget);
   if (p_dockwidget != nullptr){
      if (p_dockwidget->isHidden()){
         p_dockwidget->show();
      } else {
         p_dockwidget->hide();
      }
   }
}

void MainWindow::windowVisChanged(bool visible)
{
   std::ignore = visible;

   if (sender() == ui->dockwidg_raw_data){
      p_act_raw_data->setChecked(!ui->dockwidg_raw_data->isHidden());
   } else if (sender() == ui->dockwidg_messages){
      p_act_messages->setChecked(!ui->dockwidg_messages->isHidden());
   }

}




void MainWindow::mySaveState()
{
   QSettings settings("Test", "Test Dock Problem");
   settings.setValue("MainWindow/State", saveState());
   settings.setValue("MainWindow/Geometry", geometry());
}

void MainWindow::myRestoreState()
{
   QSettings settings("Test", "Test Dock Problem");
   restoreState(settings.value("MainWindow/State").toByteArray());
   setGeometry(settings.value("MainWindow/Geometry").toRect());
   show();
}


/* protected    */

/* public       */


