/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QDockWidget>

#include "handler_view.h"
#include "mainwindow.h"


#include "bt_reqhandler.h"


using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

HandlerView::HandlerView(
        MainWindow &mainwindow,
        std::shared_ptr<BTCore::ReqHandler> p_handler
        ) :
    mainwindow(mainwindow),
    p_handler(p_handler),
    p_dock(),
    p_list_item_widget(nullptr)
{


    //-- setup edit dockwidget
    {
        QWidget *p_edit_widg = createEditWidget();
        p_dock = make_shared<QDockWidget>(getEditDockWidgetTitle());
        //TODO: probably use some unique key instead of human-readable name
        p_dock->setObjectName("handler: " + p_handler->getTitle());
        p_dock->setWidget(p_edit_widg);

        connect(
                p_handler.get(), &BTCore::ReqHandler::titleChanged,
                this, &HandlerView::onReqHandlerTitleChanged
               );
    }
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

QWidget *HandlerView::createEditWidget()
{
    QWidget *p_widg = new QWidget();

    QBoxLayout *p_vert_lay = new QBoxLayout(QBoxLayout::TopToBottom);

    {
        QLineEdit *p_title = new QLineEdit(p_handler->getTitle());
        p_vert_lay->addWidget(p_title);

        p_script_edit = new QPlainTextEdit(p_handler->getScript());
        p_vert_lay->addWidget(p_script_edit);

        connect(
                p_title, &QLineEdit::textChanged,
                this, &HandlerView::onTitleChangedByUser
               );

        connect(
                p_script_edit, &QPlainTextEdit::textChanged,
                this, &HandlerView::onScriptChangedByUser
               );

    }

    p_widg->setLayout(p_vert_lay);

    return p_widg;
}

QWidget *HandlerView::createListItemWidget()
{
    QWidget *p_widg = new QWidget();

    QBoxLayout *p_vert_lay = new QBoxLayout(QBoxLayout::LeftToRight);

    {
        p_list_item_label_name = new QLabel(getListItemWidgetTitle());
        p_vert_lay->addWidget(p_list_item_label_name);
    }

    {
        QPushButton *p_edit_button = new QPushButton("Edit");
        p_vert_lay->addWidget(p_edit_button);

        connect(
                p_edit_button, &QPushButton::clicked,
                this, &HandlerView::onEditButtonPressed
               );
    }

    p_widg->setLayout(p_vert_lay);

    return p_widg;
}

#if 0
void HandlerView::applyReqName()
{
    p_dock->setWindowTitle("Handler " + p_handler->getTitle());
}
#endif

QString HandlerView::getEditDockWidgetTitle() const
{
    return "Handler #x: " + p_handler->getTitle();
}

QString HandlerView::getListItemWidgetTitle() const
{
    return p_handler->getTitle();
}


/* protected    */

/* public       */

QWidget *HandlerView::getListItemWidget()
{
    if (p_list_item_widget == nullptr){
        p_list_item_widget = createListItemWidget();
    }

    return p_list_item_widget;
}

QDockWidget *HandlerView::getEditDockWidget() const
{
    return p_dock.get();
}



/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void HandlerView::onEditButtonPressed()
{
    if (p_dock->isHidden()){
        p_dock->show();
    } else {
        p_dock->hide();
    }

#if 0
    //qDebug("pressed");
    QWidget *p_edit_widg = createEditWidget();
    mainwindow.addHandlerEditWidget(
            p_handler,
            p_edit_widg
            );
#endif
}

void HandlerView::onTitleChangedByUser(const QString &text)
{
    p_handler->setTitle(text);
}

void HandlerView::onScriptChangedByUser()
{
    p_handler->setScript(p_script_edit->toPlainText());
}

void HandlerView::onReqHandlerTitleChanged(const QString &text)
{
    std::ignore = text;

    p_dock->setWindowTitle(getEditDockWidgetTitle());
    p_list_item_label_name->setText(getListItemWidgetTitle());
}



/* protected    */

/* public       */


