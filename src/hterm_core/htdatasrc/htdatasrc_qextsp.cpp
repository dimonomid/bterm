/*****************************************************************************************
 *   Description:   TODO
 *
 *****************************************************************************************/

/******************************************************************************************
 * INCLUDED FILES
 *****************************************************************************************/

#include "dtdatasrc_qextsp.h"
#include <QIODevice>

#include <QDebug>

/******************************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 *****************************************************************************************/

DTDataSrcQExtSP::DTDataSrcQExtSP(const QString &port_name, BaudRateType baud_rate)
{
   qDebug() << "hi there";
   this->p_port = new QextSerialPort(port_name, QextSerialPort::EventDriven);
   p_port->setBaudRate(baud_rate);
   p_port->setFlowControl(FLOW_OFF);
   p_port->setParity(PAR_NONE);
   p_port->setDataBits(DATA_8);
   p_port->setStopBits(STOP_2);

   this->reopen();
}

DTDataSrcQExtSP::~DTDataSrcQExtSP()
{
   delete this->p_port;
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

int DTDataSrcQExtSP::bytesAvailable()
{
   return this->p_port->bytesAvailable();
}

void DTDataSrcQExtSP::read(char *data, qint64 maxlen)
{
   this->p_port->read(data, maxlen);
}

void DTDataSrcQExtSP::write(const char *data, qint64 len)
{
   this->p_port->write(data, len);
}

void DTDataSrcQExtSP::setPortName(const QString & name)
{
   this->p_port->setPortName(name);
}

void DTDataSrcQExtSP::setBaudRate(BaudRateType baudRate)
{
   this->p_port->setBaudRate(baudRate);
}

void DTDataSrcQExtSP::reopen()
{
   if (this->p_port->isOpen()){
      this->p_port->close();
   }

   if (this->p_port->open(QIODevice::ReadWrite) == true) {
      connect(p_port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
      //connect(p_port, SIGNAL(dsrChanged(bool)), this, SLOT(onDsrChanged(bool)));
      if (!(p_port->lineStatus() & LS_DSR))
         qDebug() << "warning: device is not turned on";
      qDebug() << "listening for data on" << p_port->portName();
   } else {
      qDebug() << "device failed to open:" << p_port->errorString();
   }
}

/******************************************************************************************
 * SLOTS
 *****************************************************************************************/

/* private      */

void DTDataSrcQExtSP::onReadyRead()
{
   //qDebug("DTDataSrcQExtSP onReadyRead, available=%d", static_cast<int>(this->p_port->bytesAvailable()));
   emit readyRead();
}

/* protected    */

/* public       */


