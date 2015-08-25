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
#include <QVariant>

#include <memory>
#include <vector>
#include <cstdint>

#include "bt_bytearr_read.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class ByteArrReadWrite;
}

/**
 * Class that provides read-write byte array functionality for scripts. It
 * allows writing and reading signed and unsigned integer values of various
 * sizes to and from underlying byte array.
 *
 * It extends read-only byte array `#BTCore::ByteArrRead`, see its API for
 * reading.
 */
class BTCore::ByteArrReadWrite : public BTCore::ByteArrRead
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/

public:

    /**
     * Constructs empty byte array
     */
    Q_INVOKABLE explicit ByteArrReadWrite();

    /**
     * Constructs byte array from vector of `uint8_t`
     */
    explicit ByteArrReadWrite(const std::vector<uint8_t> &data);

    /**
     * Constructs byte array of specified size, filled with specified value.
     */
    explicit ByteArrReadWrite(size_t size, uint8_t fill_byte);


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    //-- byte value with which array will be filled when extending it.
    uint8_t fill_byte;



    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/

public:

    /*
     * NOTE: we have to specify fully-qualified type name
     * `BTCore::ByteArrReadWrite`, because otherwise QJSEngine doesn't
     * recognize the type name.
     */

    /**
     * Set value with which array will be filled when extending it.
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *setFillByte(double fill_byte);

    /**
     * Put unsigned 8-bit value to byte array at specified index. If index is
     * too large, array will be extended as necessary, "unused" data will be
     * filled with `fill_byte` (see `#setFillByte()`)
     *
     * To be called from scripts.
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *putU08(
            double index,
            double val
            );

    /**
     * Put unsigned 16-bit value to byte array at specified index. If index is
     * too large, array will be extended as necessary, "unused" data will be
     * filled with `fill_byte` (see `#setFillByte()`)
     *
     * To be called from scripts.
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *putU16(
            double index,
            double val,
            double end = LITTLE_END
            );

    /**
     * Put unsigned 32-bit value to byte array at specified index. If index is
     * too large, array will be extended as necessary, "unused" data will be
     * filled with `fill_byte` (see `#setFillByte()`)
     *
     * To be called from scripts.
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *putU32(
            double index,
            double val,
            double end = LITTLE_END
            );

    /**
     * Put signed 8-bit value to byte array at specified index. If index is
     * too large, array will be extended as necessary, "unused" data will be
     * filled with `fill_byte` (see `#setFillByte()`)
     *
     * To be called from scripts.
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *putS08(
            double index,
            double val
            );

    /**
     * Put signed 16-bit value to byte array at specified index. If index is
     * too large, array will be extended as necessary, "unused" data will be
     * filled with `fill_byte` (see `#setFillByte()`)
     *
     * To be called from scripts.
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *putS16(
            double index,
            double val,
            double end = LITTLE_END
            );

    /**
     * Put signed 32-bit value to byte array at specified index. If index is
     * too large, array will be extended as necessary, "unused" data will be
     * filled with `fill_byte` (see `#setFillByte()`)
     *
     * To be called from scripts.
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *putS32(
            double index,
            double val,
            double end = LITTLE_END
            );

    /**
     * Put array of bytes to byte array at specified index. If index is too
     * large, array will be extended as necessary, "unused" data will be filled
     * with `fill_byte` (see `#setFillByte()`)
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *putU08Array(
            double index,
            QVariantList data
            );

    /**
     * Fill specified area with specified value. If index is too large, array
     * will be extended as necessary, "unused" data will be filled with
     * `fill_byte` (see `#setFillByte()`)
     */
    Q_INVOKABLE BTCore::ByteArrReadWrite *fillU08(
            double index,
            double value,
            double length
            );



private:

    void ensureSize(size_t size_needed);


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BYTEARR_READ_WRITE_H
