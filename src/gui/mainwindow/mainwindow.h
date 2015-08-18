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
class QPlainTextEdit_My;



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

   std::vector<std::shared_ptr<HandlerView>> handler_views;

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

   void addHandlerEditWidget(
         std::shared_ptr<HTCore::ReqHandler> p_handler,
         QWidget *p_widg
         );



private:

   void populateWithProject(std::shared_ptr<HTCore::Project> p_project);
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

   void onProjectOpened(std::shared_ptr<HTCore::Project> p_project);

   void onNewDataRaw(std::shared_ptr<HTCore::EventDataRaw> event_data_raw);
   void onNewDataMsg(std::shared_ptr<HTCore::EventDataMsg> event_data_msg);

};

#endif // MAINWINDOW_H
