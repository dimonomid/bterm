/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BYTEARR_READ_H
#define _BYTEARR_READ_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QObject>

#include <memory>
#include <vector>
#include <cstdint>


/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class ByteArrRead;
}

/**
 * Class that provides read-only byte array functionality for scripts. It
 * allows reading signed and unsigned integer values of various sizes from
 * underlying byte array.
 */
class BTCore::ByteArrRead : public QObject
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

public:
    /**
     * Endianness of integer value: little-endian or big-endian
     */
    enum Endianness {
        LITTLE_END,
        BIG_END
    };

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    /**
     * Construct byte array from vector of `uint8_t`
     */
    explicit ByteArrRead(const std::vector<uint8_t> &data);
    virtual ~ByteArrRead();



    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
protected:

    //-- underlying byte array
    std::shared_ptr<std::vector<uint8_t>> p_data;



    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/

public:

    /**
     * Return underlying data
     */
    std::shared_ptr<const std::vector<uint8_t>> getData() const;

    /**
     * Get byte array length.
     *
     * To be called from scripts.
     */
    Q_INVOKABLE double getLength();

    /**
     * Get unsigned 8-bit value from byte array by index. If index is too large,
     * `0xff` is returned.
     *
     * To be called from scripts.
     */
    Q_INVOKABLE double getU08(unsigned int index);

    /**
     * Get unsigned 16-bit value from byte array by index. If index is too
     * large, `0xffff` is returned.
     *
     * To be called from scripts.
     */
    Q_INVOKABLE double getU16(unsigned int index, int end = LITTLE_END);

    /**
     * Get unsigned 32-bit value from byte array by index. If index is too
     * large, `0xffffffff` is returned.
     *
     * To be called from scripts.
     */
    Q_INVOKABLE double getU32(unsigned int index, int end = LITTLE_END);

    /**
     * Get signed 8-bit value from byte array by index. If index is too large,
     * `0xff` is returned.
     *
     * To be called from scripts.
     */
    Q_INVOKABLE double getS08(unsigned int index);

    /**
     * Get signed 16-bit value from byte array by index. If index is too
     * large, `0xffff` is returned.
     *
     * To be called from scripts.
     */
    Q_INVOKABLE double getS16(unsigned int index, int end = LITTLE_END);

    /**
     * Get unsigned 32-bit value from byte array by index. If index is too
     * large, `0xffffffff` is returned.
     *
     * To be called from scripts.
     */
    Q_INVOKABLE double getS32(unsigned int index, int end = LITTLE_END);


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/




    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/

};


#endif // _BYTEARR_READ_H
