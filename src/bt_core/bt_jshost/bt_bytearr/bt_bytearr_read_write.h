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

#include "bt_bytearr_read.h"


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class ByteArrReadWrite;
}

/*
 * TODO: implement the fill byte
 *       implement unit tests
 */

/**
 * TODO
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

    /*
     * NOTE: we have to specify fully-qualified type name
     * `BTCore::ByteArrReadWrite`, because otherwise QJSEngine doesn't
     * recognize the type name.
     */

    Q_INVOKABLE BTCore::ByteArrReadWrite *setFillByte(double fill_byte);

    Q_INVOKABLE BTCore::ByteArrReadWrite *putU08(
            double index,
            double val
            );

    Q_INVOKABLE BTCore::ByteArrReadWrite *putU16(
            double index,
            double val,
            double end = LITTLE_END
            );

    Q_INVOKABLE BTCore::ByteArrReadWrite *putU32(
            double index,
            double val,
            double end = LITTLE_END
            );

    Q_INVOKABLE BTCore::ByteArrReadWrite *putS08(
            double index,
            double val
            );

    Q_INVOKABLE BTCore::ByteArrReadWrite *putS16(
            double index,
            double val,
            double end = LITTLE_END
            );

    Q_INVOKABLE BTCore::ByteArrReadWrite *putS32(
            double index,
            double val,
            double end = LITTLE_END
            );



private:

    void ensureSize(size_t size_needed);


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BYTEARR_READ_WRITE_H
