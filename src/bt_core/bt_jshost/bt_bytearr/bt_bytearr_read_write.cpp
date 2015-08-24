/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bt_bytearr_read_write.h"

#include <algorithm>


using namespace BTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ByteArrReadWrite::ByteArrReadWrite() :
    ByteArrRead(std::vector<uint8_t>()),
    fill_byte(0x00)
{
}

ByteArrReadWrite::ByteArrReadWrite(const std::vector<uint8_t> &data) :
    ByteArrRead(data),
    fill_byte(0x00)
{
}

ByteArrReadWrite::ByteArrReadWrite(size_t size, uint8_t fill_byte) :
    ByteArrRead(std::vector<uint8_t>(size, fill_byte)),
    fill_byte(fill_byte)
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

void ByteArrReadWrite::ensureSize(size_t size_needed)
{
    if (p_data->size() < size_needed){
        size_t size_before = p_data->size();
        p_data->resize(size_needed);
        std::fill(
                p_data->begin() + size_before,
                p_data->begin() + size_needed,
                fill_byte
                );
    }
}

/* protected    */

/* public       */

void ByteArrReadWrite::setFillByte(double fill_byte)
{
    this->fill_byte = fill_byte;
}


void ByteArrReadWrite::putU08(double index, double val)
{
    uint8_t actual_val = val;
    ensureSize(index + sizeof(actual_val));

    (*p_data)[index] = val;
}

void ByteArrReadWrite::putU16(double index, double val, double/*Endianness*/ end)
{
    uint16_t actual_val = val;
    ensureSize(index + sizeof(actual_val));

    switch (static_cast<int>(end)){
        case LITTLE_END:
            (*p_data)[index + 0] = ((uint8_t *)(&actual_val))[0];
            (*p_data)[index + 1] = ((uint8_t *)(&actual_val))[1];
            break;
        case BIG_END:
            (*p_data)[index + 0] = ((uint8_t *)(&actual_val))[1];
            (*p_data)[index + 1] = ((uint8_t *)(&actual_val))[0];
            break;
    }
}

void ByteArrReadWrite::putU32(double index, double val, double/*Endianness*/ end)
{
    uint32_t actual_val = val;
    ensureSize(index + sizeof(actual_val));

    switch (static_cast<int>(end)){
        case LITTLE_END:
            (*p_data)[index + 0] = ((uint8_t *)(&actual_val))[0];
            (*p_data)[index + 1] = ((uint8_t *)(&actual_val))[1];
            (*p_data)[index + 2] = ((uint8_t *)(&actual_val))[2];
            (*p_data)[index + 3] = ((uint8_t *)(&actual_val))[3];
            break;
        case BIG_END:
            (*p_data)[index + 0] = ((uint8_t *)(&actual_val))[3];
            (*p_data)[index + 1] = ((uint8_t *)(&actual_val))[2];
            (*p_data)[index + 2] = ((uint8_t *)(&actual_val))[1];
            (*p_data)[index + 3] = ((uint8_t *)(&actual_val))[0];
            break;
    }
}

void ByteArrReadWrite::putS08(double index, double val)
{
    int8_t actual_val = val;
    ensureSize(index + sizeof(actual_val));

    (*p_data)[index] = val;
}

void ByteArrReadWrite::putS16(double index, double val, double/*Endianness*/ end)
{
    int16_t actual_val = val;
    ensureSize(index + sizeof(actual_val));

    switch (static_cast<int>(end)){
        case LITTLE_END:
            (*p_data)[index + 0] = ((uint8_t *)(&actual_val))[0];
            (*p_data)[index + 1] = ((uint8_t *)(&actual_val))[1];
            break;
        case BIG_END:
            (*p_data)[index + 0] = ((uint8_t *)(&actual_val))[1];
            (*p_data)[index + 1] = ((uint8_t *)(&actual_val))[0];
            break;
    }
}

void ByteArrReadWrite::putS32(double index, double val, double/*Endianness*/ end)
{
    int32_t actual_val = val;
    ensureSize(index + sizeof(actual_val));

    switch (static_cast<int>(end)){
        case LITTLE_END:
            (*p_data)[index + 0] = ((uint8_t *)(&actual_val))[0];
            (*p_data)[index + 1] = ((uint8_t *)(&actual_val))[1];
            (*p_data)[index + 2] = ((uint8_t *)(&actual_val))[2];
            (*p_data)[index + 3] = ((uint8_t *)(&actual_val))[3];
            break;
        case BIG_END:
            (*p_data)[index + 0] = ((uint8_t *)(&actual_val))[3];
            (*p_data)[index + 1] = ((uint8_t *)(&actual_val))[2];
            (*p_data)[index + 2] = ((uint8_t *)(&actual_val))[1];
            (*p_data)[index + 3] = ((uint8_t *)(&actual_val))[0];
            break;
    }
}





/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


