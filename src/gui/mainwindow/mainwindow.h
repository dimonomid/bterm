#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <cstdint>

#include <QMainWindow>


class HTDataMsg;

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

   void onNewDataRaw(const std::vector<uint8_t> &data);
   void onNewDataMsg(const HTDataMsg &msg);

};

#endif // MAINWINDOW_H
