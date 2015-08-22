/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _BT_DATAPART_H
#define _BT_DATAPART_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>

#include <vector>



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace BTCore {
    class DataPart;
}


/**
 * Class that represents a part of data message (see `#BTCore::DataMsg`). The
 * message contains both service data (that is transmitted on the wire) and
 * user data (the payload). To this end, the message consists of parts,
 * represented by this class.
 *
 * Each part is of some type (see `#PartType`).
 */
class BTCore::DataPart
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/
public:

    /**
     * Type of the data: service or user.
     */
    enum class DataType {

        /** Service data (that is transmitted on the wire)
         */
        SERVICE,

        /** User data (the payload of the message)
         */
        USER,
    };

    /**
     * Type of the data part. See each type for details.
     */
    enum class PartType {

        /** Service: the part contains only data of type
         * `DataType::SERVICE`.
         */
        SERVICE,

        /** User: the part contains only data of type
         * `DataType::USER`.
         */
        USER,

        /** Combined: the part contains data of both types (service and user).
         * This may happen when the payload data is represented by different
         * service data. For example, it happens if we have some "escape
         * sequences": say, we may have byte `0xfe` to have some special meaning,
         * and in order to encode exactly this byte `0xfe`, we must double it.
         */
        COMBINED,

        /** The part doesn't yet contain any data.
         */
        EMPTY,
    };

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:

    /**
     * Construct empty data part
     */
    explicit DataPart();

    /**
     * Construct data part that contains data of specified type.
     *
     * @param data_type
     *      type of data
     * @param data
     *      the data itself
     */
    explicit DataPart(DataType data_type, const std::vector<uint8_t> &data);
    explicit DataPart(DataType data_type, std::vector<uint8_t> &&data);

    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:
    //-- data of type `DataType::SERVICE`
    std::vector<uint8_t> service_data;
    //-- data of type `DataType::USER`
    std::vector<uint8_t> user_data;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    /**
     * Add data of specified type.
     */
    void addData(DataType data_type, const std::vector<uint8_t> &data);

    /**
     * Add byte to data of specified type.
     */
    void addDataByte(DataType data_type, uint8_t byte);

    /**
     * Get data of specified type.
     */
    std::vector<uint8_t> getData(DataType data_type) const;

    /**
     * Get type of this data part. See `#PartType` for details.
     */
    PartType getType() const;

    /**
     * Returns whether data of given type could be added to the data part
     * without breaking part's homogeneity.
     *
     * If the part is already non-homogeneous, false is returned
     * intependently of given data_type.
     *
     * The part is homogeneous if it is either empty or contains
     * data of only single type (`DataType::SERVICE` or
     * `DataType::USER`), but not both.
     *
     * @param data_type
     *      data type to consider
     */
    bool canDataBeAddedHomogeneously(DataType data_type) const;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/


    /*******************************************************************************
     * OPERATORS
     ******************************************************************************/

public:
    inline bool operator==(const DataPart &other) const {
        return (this->user_data == other.user_data && this->service_data == other.service_data);
    }
};


#endif // _BT_DATAPART_H
