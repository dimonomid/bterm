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

   QBoxLayout *p_vert_lay = new QBoxLayout(QBoxLayout::TopToBottom);

   {
      QLabel *p_label = new QLabel("Handler: " + p_handler->getName());
      p_vert_lay->addWidget(p_label);
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

/* protected    */

/* public       */


