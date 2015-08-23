/******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _DTDATASRC_H
#define _DTDATASRC_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>
#include <vector>

#include <QObject>

/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class IODev;
}

/**
 * Abstract class that represents IO device: arbitrary data can be read from it
 * and written to it.
 *
 * A pointer to an instance of concrete implementation of this abstract class
 * should be given to `#BTCore::Project` via `#BTCore::Project::setIODev()`,
 * and all communication with remote device will be done through that IO
 * device.
 */
class BTCore::IODev : public QObject
{
Q_OBJECT
    /*******************************************************************************
     * TYPES
     ******************************************************************************/

    /*******************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ******************************************************************************/
public:

    /*******************************************************************************
     * PRIVATE DATA
     ******************************************************************************/
private:

    /*******************************************************************************
     * STATIC METHODS
     ******************************************************************************/

    /*******************************************************************************
     * METHODS
     ******************************************************************************/
public:

    /**
     * Set baud rate. This function should be called only when port is not opened.
     */
    virtual void setBaudRate(int32_t baud_rate) = 0;

    /**
     * Get baud rate.
     */
    virtual int32_t getBaudRate() = 0;

    /**
     * Open serial port
     */
    virtual void open() = 0;

    /**
     * Close serial port
     */
    virtual void close() = 0;

    /**
     * Returns whether the port is opened
     */
    virtual bool isOpened() = 0;

    /**
     * Read all available data from serial port as a `vector<uint8_t>`.
     * If no data is available, empty `vector` is returned.
     */
    virtual std::vector<uint8_t> read() = 0;

    /**
     * Write data to serial port.
     */
    virtual void write(const std::vector<uint8_t> &data) = 0;

    virtual QString toString() = 0;


    /*******************************************************************************
     * SIGNALS, SLOTS
     ******************************************************************************/

signals:

    /**
     * Emitted when new data becomes available.
     *
     * @param bytes_available
     *      total bytes available for reading at the moment. For example,
     *      if 10 bytes arrive, this signal is emitted with value 10.
     *      If nobody reads this data, and 2 more bytes arrive, then
     *      this signal is emitted with value 12.
     */
    void readyRead(int bytes_available);

    /**
     * Emitted whenever port gets opened or closed.
     */
    void openStatusChanged(bool opened);

    /**
     * Emitted whenever IO error occurs
     */
    void error(QString error_msg);


};


#endif // _DTDATASRC_H
