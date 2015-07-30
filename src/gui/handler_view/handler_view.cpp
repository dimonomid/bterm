/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>

#include "handler_view.h"
#include "mainwindow.h"


#include "htreqhandler.h"

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HandlerView::HandlerView(
      MainWindow &mainwindow,
      std::shared_ptr<HTCore::ReqHandler> p_handler
      ) :
   mainwindow(mainwindow),
   p_handler(p_handler)
{
}



/*******************************************************************************
 * STATIC METHODS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


/*******************************************************************************
 * METHODS
 ******************************************************************************/

/* private      */

QWidget *HandlerView::createEditWidget() const
{
   QWidget *p_widg = new QWidget();

   QBoxLayout *p_vert_lay = new QBoxLayout(QBoxLayout::TopToBottom);

   {
      QPlainTextEdit *p_code = new QPlainTextEdit(p_handler->getScript());
      p_vert_lay->addWidget(p_code);
   }

   p_widg->setLayout(p_vert_lay);

   return p_widg;
}


/* protected    */

/* public       */

QWidget *HandlerView::createListItemWidget() const
{
   QWidget *p_widg = new QWidget();

   QBoxLayout *p_vert_lay = new QBoxLayout(QBoxLayout::LeftToRight);

   {
      QLabel *p_label = new QLabel("Handler: " + p_handler->getName());
      p_vert_lay->addWidget(p_label);
   }

   {
      QPushButton *p_edit_button = new QPushButton("Edit");
      p_vert_lay->addWidget(p_edit_button);

      connect(
            p_edit_button, &QPushButton::clicked,
            this, &HandlerView::onEditButtonPressed
            );
   }

   //TODO: make button like "edit", and when it's pressed, new dock widget
   //      should be created.
   //
   //      Need to think how to account these dock widgets: the GUI
   //      should be prepared to handle event when scripts are changed
   //      from outside (although it is not going to happen, but anyway)
#if 0
   {
      QPlainTextEdit *p_code = new QPlainTextEdit(p_handler->getScript());
      p_vert_lay->addWidget(p_code);
      p_code->setHidden(true);
   }
#endif

   p_widg->setLayout(p_vert_lay);
   
   return p_widg;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void HandlerView::onEditButtonPressed()
{
   //qDebug("pressed");
   QWidget *p_edit_widg = createEditWidget();
   mainwindow.addHandlerEditWidget(
         p_handler,
         p_edit_widg
         );
}



/* protected    */

/* public       */


