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

namespace HTCore {
    class IODev;
}

/**
 * Abstract class that represents IO device: arbitrary data can be read from it
 * and written to it.
 *
 * A pointer to an instance of concrete implementation of this abstract class
 * should be given to `#HTCore::Project` via `#HTCore::Project::setIODev()`,
 * and all communication with remote device will be done through that IO
 * device.
 */
class HTCore::IODev : public QObject
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
     * Read all available data from serial port as a `vector<uint8_t>`.
     * If no data is available, empty `vector` is returned.
     */
    virtual std::vector<uint8_t> read() = 0;

    /**
     * Write data to serial port.
     */
    virtual void write(const std::vector<uint8_t> &data) = 0;



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


};


#endif // _DTDATASRC_H
