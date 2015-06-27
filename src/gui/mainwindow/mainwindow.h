#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <memory>
#include <cstdint>

#include <QMainWindow>


//class HTDataMsg;
class HTEventDataRaw;
class HTEventDataMsg;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private:
   Ui::MainWindow *ui;


   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/
private slots:

   void onNewDataRaw(const std::shared_ptr<HTEventDataRaw> &event_data_raw);
   void onNewDataMsg(const std::shared_ptr<HTEventDataMsg> &event_data_msg);

};

#endif // MAINWINDOW_H
