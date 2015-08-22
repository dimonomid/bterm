/*****************************************************************************************
 *   Description:   TODO
 *
 *****************************************************************************************/

#ifndef _DTDATASRC_QEXTSP_H
#define _DTDATASRC_QEXTSP_H

/******************************************************************************************
 * INCLUDED FILES
 *****************************************************************************************/

#include "dtdatasrc.h"
#include "qextserialport.h"

/******************************************************************************************
 * CLASS DECLARATION
 *****************************************************************************************/

class DTDataSrcQExtSP : public DTDataSrc
{
Q_OBJECT
    /******************************************************************************************
     * TYPES
     *****************************************************************************************/

    /******************************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     *****************************************************************************************/
public:
    DTDataSrcQExtSP(const QString &port_name, BaudRateType baud_rate);
    virtual ~DTDataSrcQExtSP();

    /******************************************************************************************
     * PRIVATE DATA
     *****************************************************************************************/
private:
    QextSerialPort *p_port;

    /******************************************************************************************
     * STATIC METHODS
     *****************************************************************************************/

    /******************************************************************************************
     * METHODS
     *****************************************************************************************/
public:
    int  bytesAvailable();
    void read   (char *data, qint64 maxlen);
    void write  (const char *data, qint64 len);

    void setPortName(const QString & name);
    void setBaudRate(BaudRateType baudRate);
    void reopen();

    /******************************************************************************************
     * SIGNALS, SLOTS
     *****************************************************************************************/
private slots:
    void onReadyRead();


};


#endif // _DTDATASRC_QEXTSP_H