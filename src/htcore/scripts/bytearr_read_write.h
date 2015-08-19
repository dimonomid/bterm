/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BYTEARR_READ_WRITE_H
#define _BYTEARR_READ_WRITE_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include <memory>
#include <vector>
#include <cstdint>

#include "bytearr_read.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class ByteArrReadWrite;
}

/*
 * TODO: implement the fill byte
 *       implement unit tests
 */

/**
 * TODO
 */
class HTCore::ByteArrReadWrite : public HTCore::ByteArrRead
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    Q_INVOKABLE explicit ByteArrReadWrite();
    explicit ByteArrReadWrite(const std::vector<uint8_t> &data);
    explicit ByteArrReadWrite(size_t size, uint8_t fill_byte);


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    uint8_t fill_byte;



    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/

public:
    Q_INVOKABLE void setFillByte(unsigned int fill_byte);

    Q_INVOKABLE void putU08(unsigned int index, double val);
    Q_INVOKABLE void putU16(unsigned int index, double val, int end = LITTLE_END);
    Q_INVOKABLE void putU32(unsigned int index, double val, int end = LITTLE_END);

    Q_INVOKABLE void putS08(unsigned int index, double val);
    Q_INVOKABLE void putS16(unsigned int index, double val, int end = LITTLE_END);
    Q_INVOKABLE void putS32(unsigned int index, double val, int end = LITTLE_END);



private:

    void ensureSize(size_t size_needed);


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BYTEARR_READ_WRITE_H
