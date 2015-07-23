#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <memory>
#include <cstdint>

#include <QMainWindow>
#include <QSignalMapper>


//class HTDataMsg;
class HTEventDataRaw;
class HTEventDataMsg;

namespace Ui {
   class MainWindow;
}

class Appl;


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


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/
private slots:

   void onNewDataRaw(std::shared_ptr<HTEventDataRaw> event_data_raw);
   void onNewDataMsg(std::shared_ptr<HTEventDataMsg> event_data_msg);

   void toolbarToggle(QWidget *p_widget);
   void windowVisChanged(bool visible);

   void mySaveState();
   void myRestoreState();

};

#endif // MAINWINDOW_H
