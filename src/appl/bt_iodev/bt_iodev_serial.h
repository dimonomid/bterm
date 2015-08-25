/*******************************************************************************
 *   Description:   TODO
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
    std::vector<uint8_t> cur_data;

    int stage;
    bool opened;
    int baudrate;

    std::unique_ptr<QSerialPort> p_port;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    std::vector<uint8_t> read() override;
    void write(const std::vector<uint8_t> &data) override;
    void setBaudRate(int32_t baud_rate) override;
    int32_t getBaudRate() override;
    void open() override;
    void close() override;
    bool isOpened() override;
    QString toString() override;


    void setPortName(QString name);


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:
    //NOTE: we should NOT define signals in subclasses,
    //      since if we do, then function pointer-based
    //      connect() syntax will not generate any errors,
    //      but it will just not work silently.
    //
    //void readyRead(int bytes_available);

private slots:

    void onReadyRead();




    /****************************************************************************
     * OPERATORS
     ***************************************************************************/

};


#endif // _BT_IODEV_SERIAL_H
