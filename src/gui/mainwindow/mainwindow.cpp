
#include <QString>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "htdatamsg.h"

#include "my_util.h"

MainWindow::MainWindow(
      QWidget *parent
      ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void MainWindow::onNewDataRaw(const std::vector<uint8_t> &data)
{
   QString text = MyUtil::byteArrayToHex(data) + "<br>";

   this->ui->pte_raw_data->appendHtmlNoNL(text, true);

#if 0
   QTextCursor cursor = QTextCursor(this->ui->pte_raw_data->document());
   cursor.movePosition(QTextCursor::End);
   cursor.insertHtml(text);
   cursor.movePosition(QTextCursor::End);
#endif
}

void MainWindow::onNewDataMsg(const HTDataMsg &msg)
{
   QString text = "<b>msg: </b>" + MyUtil::byteArrayToHex(msg.getUserData()) + "<br>";

   this->ui->pte_messages->appendHtmlNoNL(text, true);


#if 0
   QTextCursor cursor = QTextCursor(this->ui->pte_messages->document());
   cursor.movePosition(QTextCursor::End);
   cursor.insertHtml(text);
   cursor.movePosition(QTextCursor::End);
#endif
}

/* protected    */

/* public       */


