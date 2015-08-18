/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "bytearr_read.h"


using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

ByteArrRead::ByteArrRead(const std::vector<uint8_t> &data) :
    p_data(std::make_shared<std::vector<uint8_t>>(data))
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

double ByteArrRead::getU08(unsigned int index)
{
    uint8_t ret;

    if (p_data->size() < (index + sizeof(ret))){
        //-- size of data is not enough
        ret = -1;
    } else {
        ret = (*p_data)[index];
    }

    return ret;
}

double ByteArrRead::getU16(unsigned int index, int/*Endianness*/ end)
{
    uint16_t ret;

    if (p_data->size() < (index + sizeof(ret))){
        //-- size of data is not enough
        ret = -1;
    } else {
        switch (end){
            case LITTLE_END:
                ((uint8_t *)(&ret))[0] = (*p_data)[index + 0];
                ((uint8_t *)(&ret))[1] = (*p_data)[index + 1];
                break;
            case BIG_END:
                ((uint8_t *)(&ret))[0] = (*p_data)[index + 1];
                ((uint8_t *)(&ret))[1] = (*p_data)[index + 0];
                break;
        }
    }

    return ret;
}

double ByteArrRead::getU32(unsigned int index, int/*Endianness*/ end)
{
    uint32_t ret;

    if (p_data->size() < (index + sizeof(ret))){
        //-- size of data is not enough
        ret = -1;
    } else {
        switch (end){
            case LITTLE_END:
                ((uint8_t *)(&ret))[0] = (*p_data)[index + 0];
                ((uint8_t *)(&ret))[1] = (*p_data)[index + 1];
                ((uint8_t *)(&ret))[2] = (*p_data)[index + 2];
                ((uint8_t *)(&ret))[3] = (*p_data)[index + 3];
                break;
            case BIG_END:
                ((uint8_t *)(&ret))[0] = (*p_data)[index + 3];
                ((uint8_t *)(&ret))[1] = (*p_data)[index + 2];
                ((uint8_t *)(&ret))[2] = (*p_data)[index + 1];
                ((uint8_t *)(&ret))[3] = (*p_data)[index + 0];
                break;
        }
    }

    return ret;
}

double ByteArrRead::getS08(unsigned int index)
{
    int8_t ret;

    if (p_data->size() < (index + sizeof(ret))){
        //-- size of data is not enough
        ret = -1;
    } else {
        ret = (*p_data)[index];
    }

    return ret;
}

double ByteArrRead::getS16(unsigned int index, int/*Endianness*/ end)
{
    int16_t ret;

    if (p_data->size() < (index + sizeof(ret))){
        //-- size of data is not enough
        ret = -1;
    } else {
        switch (end){
            case LITTLE_END:
                ((uint8_t *)(&ret))[0] = (*p_data)[index + 0];
                ((uint8_t *)(&ret))[1] = (*p_data)[index + 1];
                break;
            case BIG_END:
                ((uint8_t *)(&ret))[0] = (*p_data)[index + 1];
                ((uint8_t *)(&ret))[1] = (*p_data)[index + 0];
                break;
        }
    }

    return ret;
}

double ByteArrRead::getS32(unsigned int index, int/*Endianness*/ end)
{
    int32_t ret;

    if (p_data->size() < (index + sizeof(ret))){
        //-- size of data is not enough
        ret = -1;
    } else {
        switch (end){
            case LITTLE_END:
                ((uint8_t *)(&ret))[0] = (*p_data)[index + 0];
                ((uint8_t *)(&ret))[1] = (*p_data)[index + 1];
                ((uint8_t *)(&ret))[2] = (*p_data)[index + 2];
                ((uint8_t *)(&ret))[3] = (*p_data)[index + 3];
                break;
            case BIG_END:
                ((uint8_t *)(&ret))[0] = (*p_data)[index + 3];
                ((uint8_t *)(&ret))[1] = (*p_data)[index + 2];
                ((uint8_t *)(&ret))[2] = (*p_data)[index + 1];
                ((uint8_t *)(&ret))[3] = (*p_data)[index + 0];
                break;
        }
    }

    return ret;
}




std::shared_ptr<const std::vector<uint8_t>> ByteArrRead::getData() const
{
    return p_data;
}


/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


