/*****************************************************************************************
 *   Description:   See class declaration below
 *
 *****************************************************************************************/

#ifndef _QPLAINTEXTEDIT_MY_H
#define _QPLAINTEXTEDIT_MY_H

/******************************************************************************************
 * INCLUDED FILES
 *****************************************************************************************/

#include <QPlainTextEdit>

/******************************************************************************************
 * CLASS DECLARATION
 *****************************************************************************************/

/**
 * Rather simple extension of `QPlainTextEdit` that allows to append html and
 * plain text without adding a newline.
 *
 * (see this question: http://stackoverflow.com/q/13559990/1099240)
 */
class QPlainTextEdit_My : public QPlainTextEdit
{
    /******************************************************************************************
     * TYPES
     *****************************************************************************************/

    /******************************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     *****************************************************************************************/
public:
    explicit QPlainTextEdit_My(QWidget *parent);
    explicit QPlainTextEdit_My(const QString &text, QWidget *parent);


    /******************************************************************************************
     * PRIVATE DATA
     *****************************************************************************************/
private:

    /******************************************************************************************
     * STATIC METHODS
     *****************************************************************************************/

    /******************************************************************************************
     * METHODS
     *****************************************************************************************/

public:

    /**
     * append text without adding new line (new paragraph)
     *
     * @param text       bt_ml text to append
     * @param check_nl   if true, then text will be splitted by \n char,
     *                   and each substring will be added as separate QTextBlock.
     *                   NOTE: this important: if you set this to false,
     *                   then you should append new blocks manually (say, by calling appendNL() )
     *                   because one huge block will significantly slow down your widget.
     */
    void appendPlainTextNoNL(const QString &text, bool check_nl = false);

    /**
     * append bt_ml without adding new line (new paragraph)
     *
     * @param bt_ml       bt_ml text to append
     * @param check_br   if true, then text will be splitted by "<br>" tag,
     *                   and each substring will be added as separate QTextBlock.
     *                   NOTE: this important: if you set this to false,
     *                   then you should append new blocks manually (say, by calling appendNL() )
     *                   because one huge block will significantly slow down your widget.
     */
    void appendHtmlNoNL     (const QString &bt_ml, bool check_br = false);

    /**
     * Just insert new QTextBlock to the text.
     * (in fact, adds new paragraph)
     */
    void insertNL           ();

    /******************************************************************************************
     * SIGNALS, SLOTS
     *****************************************************************************************/

};


#endif // _QPLAINTEXTEDIT_MY_H
