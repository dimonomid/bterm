/******************************************************************************
 *   Description:   TODO
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
    stage(0),
    opened(false),
    baudrate(9600),

    p_port(new QSerialPort())
{
    //TODO: configurable
    setPortName("/dev/USB_logger");

    connect(
            p_port.get(), &QSerialPort::readyRead,
            this, &IODevSerial::onReadyRead
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
}

void IODevSerial::setBaudRate(int32_t baud_rate)
{
    this->baudrate = baud_rate;

    emit baudRateChanged(baud_rate);
}

int32_t IODevSerial::getBaudRate()
{
    return baudrate;
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
    return "Debug IO device";
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


/* protected    */

/* public       */


