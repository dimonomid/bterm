#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <memory>
#include <cstdint>

#include <QMainWindow>
#include <QSignalMapper>


//class DataMsg;
namespace HTCore {
   class EventDataRaw;
   class EventDataMsg;
   class Project;
   class ReqHandler;
}

namespace Ui {
   class MainWindow;
}

class Appl;
class HandlerView;


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
   explicit MainWindow(
         Appl &appl,
         QWidget *parent = 0
         );
   ~MainWindow();

private:
   Ui::MainWindow   *ui;
   Appl &appl;

   QSignalMapper     windows_toggle_sigmap;

   QAction          *p_act_raw_data;
   QAction          *p_act_messages;

   QDockWidget      *p_dw_handlers;

   std::vector<std::shared_ptr<HandlerView>> handler_views;



   /****************************************************************************
    * METHODS
    ***************************************************************************/

public:

   void addHandlerEditWidget(
         std::shared_ptr<HTCore::ReqHandler> p_handler,
         QWidget *p_widg
         );



private:

   void populateWithProject(std::shared_ptr<HTCore::Project> p_project);



   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/
private slots:

   void onProjectOpened(std::shared_ptr<HTCore::Project> p_project);

   void onNewDataRaw(std::shared_ptr<HTCore::EventDataRaw> event_data_raw);
   void onNewDataMsg(std::shared_ptr<HTCore::EventDataMsg> event_data_msg);

   void toolbarToggle(QWidget *p_widget);
   void windowVisChanged(bool visible);

   void mySaveState();
   void myRestoreState();

};

#endif // MAINWINDOW_H
