/*****************************************************************************************
 *   Description:
 *
 *   FIXME: this class is actually a dirty hack: we shouldn't inherit
 *   QPlainTextEdit. I hope I'll have some time in the future to fix that
 *   (at least, we may use composition instead)
 *
 *****************************************************************************************/

/******************************************************************************************
 * INCLUDED FILES
 *****************************************************************************************/

#include "qplaintextedit_my.h"
#include <QScrollBar>
#include <QTextCursor>
#include <QStringList>
#include <QRegExp>


/******************************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 *****************************************************************************************/

QPlainTextEdit_My::QPlainTextEdit_My(QWidget *parent) :
   QPlainTextEdit(parent)
{

}

QPlainTextEdit_My::QPlainTextEdit_My(const QString &text, QWidget *parent) :
   QPlainTextEdit(text, parent)
{

}


/******************************************************************************************
 * STATIC METHODS
 *****************************************************************************************/

/* private      */

/* protected    */

/* public       */


/******************************************************************************************
 * METHODS
 *****************************************************************************************/

/* private      */

/* protected    */

/* public       */

/**
 * append html without adding new line (new paragraph)
 *
 * @param html       html text to append
 * @param check_nl   if true, then text will be splitted by \n char,
 *                   and each substring will be added as separate QTextBlock.
 *                   NOTE: this important: if you set this to false,
 *                   then you should append new blocks manually (say, by calling appendNL() )
 *                   because one huge block will significantly slow down your widget.
 */
void QPlainTextEdit_My::appendPlainTextNoNL(const QString &text, bool check_nl)
{
   QScrollBar *p_scroll_bar = this->verticalScrollBar();
   bool bool_at_bottom = (p_scroll_bar->value() == p_scroll_bar->maximum());

   if (!check_nl){
      //-- don't check for \n, just append all the given text

      QTextCursor text_cursor = QTextCursor(this->document());
      text_cursor.movePosition(QTextCursor::End);
      text_cursor.insertText(text);

   } else {
      //-- split text by \n and add resulting pieces as separate paragraphs

      QTextCursor text_cursor = QTextCursor(this->document());
      text_cursor.beginEditBlock();

      text_cursor.movePosition(QTextCursor::End);

      QStringList string_list = text.split('\n');

      for (int i = 0; i < string_list.size(); i++){
         text_cursor.insertText(string_list.at(i));
         if ((i + 1) < string_list.size()){
            text_cursor.insertBlock();
         }
      }


      text_cursor.endEditBlock();
   }

   if (bool_at_bottom){
      p_scroll_bar->setValue(p_scroll_bar->maximum());
   }
}

/**
 * append html without adding new line (new paragraph)
 *
 * @param html       html text to append
 * @param check_br   if true, then text will be splitted by "<br>" tag,
 *                   and each substring will be added as separate QTextBlock.
 *                   NOTE: this important: if you set this to false,
 *                   then you should append new blocks manually (say, by calling appendNL() )
 *                   because one huge block will significantly slow down your widget.
 */
void QPlainTextEdit_My::appendHtmlNoNL(const QString &html, bool check_br)
{
   QScrollBar *p_scroll_bar = this->verticalScrollBar();
   bool bool_at_bottom = (p_scroll_bar->value() == p_scroll_bar->maximum());

   if (!check_br){
      //-- don't check for <br>, just append all the given html text

      QTextCursor text_cursor = QTextCursor(this->document());
      text_cursor.movePosition(QTextCursor::End);
      text_cursor.insertHtml(html);
   } else {
      //-- split text by <br> tag, and add resulting pieces as separate paragraphs
      //   (we have to use QRegExp here, because there are many variants of tag representation )

      QTextCursor text_cursor = QTextCursor(this->document());
      text_cursor.beginEditBlock();

      text_cursor.movePosition(QTextCursor::End);

      QStringList string_list = html.split(QRegExp("\\<br\\s*\\/?\\>", Qt::CaseInsensitive));

      for (int i = 0; i < string_list.size(); i++){
         text_cursor.insertHtml( string_list.at(i) );
         if ((i + 1) < string_list.size()){
            text_cursor.insertBlock();
         }
      }

      text_cursor.endEditBlock();
   }

   if (bool_at_bottom){
      p_scroll_bar->setValue(p_scroll_bar->maximum());
   }
}

/**
 * Just insert new QTextBlock to the text.
 * (in fact, adds new paragraph)
 */
void QPlainTextEdit_My::insertNL()
{
   QScrollBar *p_scroll_bar = this->verticalScrollBar();
   bool bool_at_bottom = (p_scroll_bar->value() == p_scroll_bar->maximum());

   QTextCursor text_cursor = QTextCursor(this->document());
   text_cursor.movePosition(QTextCursor::End);
   text_cursor.insertBlock();

   if (bool_at_bottom){
      p_scroll_bar->setValue(p_scroll_bar->maximum());
   }
}

/******************************************************************************************
 * SLOTS
 *****************************************************************************************/

/* private      */

/* protected    */

/* public       */


