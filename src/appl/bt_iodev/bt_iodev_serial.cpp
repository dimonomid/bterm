/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QDebug>

#include "bt_iodev_serial.h"
#include "my_util.h"

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <tuple>


using namespace std;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

IODevSerial::IODevSerial() :
    cur_data(),
    opened(false),

    p_port(new QSerialPort())
{
    //TODO: configurable
    setPortName("/dev/USB_ecu_emulator");

    connect(
            p_port.get(), &QSerialPort::readyRead,
            this, &IODevSerial::onReadyRead
           );

    connect(
            p_port.get(),
            static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &IODevSerial::onPortError
           );
}

IODevSerial::~IODevSerial()
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

vector<uint8_t> IODevSerial::read()
{
    vector<uint8_t> ret = std::move(cur_data);
    cur_data = vector<uint8_t>{};
    return ret;
}

void IODevSerial::write(const vector<uint8_t> &data)
{
    qDebug() << "write: " << MyUtil::byteArrayToHex(data);
    int32_t written_cnt = p_port->write(reinterpret_cast<const char *>(data.data()), data.size());
    qDebug() << "written: " << written_cnt;
}

void IODevSerial::setBaudRate(int32_t baud_rate)
{
    bool set_res = p_port->setBaudRate(baud_rate);
    if (!set_res){
        qDebug("setting baud rate failed!");
    }

    emit baudRateChanged(baud_rate);
}

int32_t IODevSerial::getBaudRate()
{
    return p_port->baudRate();
}

void IODevSerial::open()
{
    bool open_res = p_port->open(QIODevice::ReadWrite);
    qDebug() << "open_res" << open_res;

    if (open_res != opened){
        opened = open_res;
        emit openStatusChanged(opened);
    }
}

void IODevSerial::close()
{
    p_port->close();
    if (opened){
        opened = false;
        emit openStatusChanged(opened);
    }
}

bool IODevSerial::isOpened()
{
    return opened;
}

QString IODevSerial::toString()
{
    return "Serial Port '"
        + p_port->portName()
        + "', " + QString::number(p_port->baudRate())
        ;
}





void IODevSerial::setPortName(QString name)
{
    p_port->setPortName(name);
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

void IODevSerial::onReadyRead()
{
    qDebug("ready read");

    uint32_t avail_size = 0;

    while ((avail_size = p_port->bytesAvailable()) > 0){
        size_t existing_size = cur_data.size();
        cur_data.resize( existing_size + avail_size );
        uint8_t *p_data = cur_data.data();
        char *p_data_char = reinterpret_cast<char *>(p_data);

        uint32_t read_size = p_port->read(
                p_data_char + existing_size, avail_size
                );

        //-- if we actually read less than was declared as "available",
        //   adjust cur_data size
        if (read_size < avail_size){
            cur_data.resize( existing_size + read_size );
        } else if (read_size > avail_size){
            //-- should never be here
            qDebug("error: read more than was available");
        }
    }

    emit readyRead(cur_data.size());
}

void IODevSerial::onPortError(QSerialPort::SerialPortError error_code)
{
    qDebug() << "port error" << (int)error_code;

    switch (error_code){

        case QSerialPort::DeviceNotFoundError:
            emit error("Device not found");
            break;

        case QSerialPort::ResourceError:
            emit error("Port resource is gone");
            close();
            break;

        default:
            break;
    }
}


/* protected    */

/* public       */


