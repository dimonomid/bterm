/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDialogButtonBox>

#include "appl_sett_dialog.h"



/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ApplSettDialog::ApplSettDialog(
        Appl &appl,
        QWidget *p_parent,
        Qt::WindowFlags flags
        ) :
    QDialog(p_parent, flags),
    appl(appl),
    ui(new Ui::ApplSettDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Project settings");

    //-- populate form with actual values
    ui->port_name->setText(appl.getIOPortName());

    //-- if IO device is currently opened, we can't edit port name
    if (appl.isIODevOpened()){
        ui->port_name->setEnabled(false);
    }


    connect(
            ui->buttons, &QDialogButtonBox::accepted,
            this, &ApplSettDialog::onOkPressed
           );

    connect(
            ui->buttons, &QDialogButtonBox::rejected,
            this, &ApplSettDialog::onCancelPressed
           );

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

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void ApplSettDialog::onOkPressed()
{

    appl.setIOPortName(ui->port_name->text());

    accept();
}

void ApplSettDialog::onCancelPressed()
{
    reject();
}




/* protected    */

/* public       */


