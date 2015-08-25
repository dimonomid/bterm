/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_IODEV_SERIAL_H
#define _BT_IODEV_SERIAL_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/


#include <QSerialPort>

#include <cstdint>
#include <vector>
#include <memory>

#include "bt_iodev.h"



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

/**
 * Implementation of `#BTCore::IODev` that works with real serial port
 * by means of `QSerialPort`.
 */
class IODevSerial : public BTCore::IODev
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT
     ***************************************************************************/
public:
    explicit IODevSerial();
    virtual ~IODevSerial();

    IODevSerial(const IODevSerial &other) = delete;
    IODevSerial(IODevSerial &&other) = delete;

    IODevSerial &operator=(const IODevSerial &other) = delete;
    IODevSerial &operator=(IODevSerial &&other) = delete;


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:
    //-- currently received data that wasn't yet read by client
    std::vector<uint8_t> cur_data;

    //-- represents whether IO device is currently opened
    bool opened;

    //-- actual serial port instance
    std::unique_ptr<QSerialPort> p_port;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * Set port name:
     *
     * - on Linux, it may be something like `/dev/tty1`
     * - on Windows, it may be something like `COM4`
     */
    void setPortName(QString name);



    //-- overridden methods from `#BTCore::IODev`

    std::vector<uint8_t> read() override;
    void write(const std::vector<uint8_t> &data) override;
    void setBaudRate(int32_t baud_rate) override;
    int32_t getBaudRate() override;
    void open() override;
    void close() override;
    bool isOpened() override;
    QString toString() override;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:

private slots:

    void onReadyRead();
    void onPortError(QSerialPort::SerialPortError error);




    /****************************************************************************
     * OPERATORS
     ***************************************************************************/

};


#endif // _BT_IODEV_SERIAL_H
