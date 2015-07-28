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
#include <QPlainTextEdit>

#include "handler_view.h"


#include "htreqhandler.h"

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HandlerView::HandlerView(
      std::shared_ptr<HTCore::ReqHandler> p_handler
      ) :
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

/* protected    */

/* public       */

QWidget *HandlerView::createWidget() const
{
   QWidget *p_widg = new QWidget();

   QBoxLayout *p_lay = new QBoxLayout(QBoxLayout::TopToBottom);

   {
      QLabel *p_label = new QLabel("Handler: " + p_handler->getName());
      p_lay->addWidget(p_label);
   }

   {
      QPlainTextEdit *p_code = new QPlainTextEdit(p_handler->getScript());
      p_lay->addWidget(p_code);
   }

   p_widg->setLayout(p_lay);
   
   return p_widg;
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


