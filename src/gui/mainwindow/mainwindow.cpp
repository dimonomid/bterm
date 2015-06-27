
#include <QString>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "htdatamsg.h"

#include "my_util.h"

#include "htevent_data_raw.h"
#include "htevent_data_msg.h"

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

void MainWindow::onNewDataRaw(const std::shared_ptr<HTEventDataRaw> &event_data_raw)
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

void MainWindow::onNewDataMsg(const std::shared_ptr<HTEventDataMsg> &event_data_msg)
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

/* protected    */

/* public       */


