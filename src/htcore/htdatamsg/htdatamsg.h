/*******************************************************************************
 *   Description:   See class declaration below
 *
 ******************************************************************************/

#ifndef _HTDATAMSG_H
#define _HTDATAMSG_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <cstdint>

#include <vector>
#include <string>
#include <memory>

#include "htdatapart.h"



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

namespace HTCore {
    class DataMsg;
}



/**
 * Class that represents single data message. The message contains both service
 * data (that is transmitted on the wire) and user data (the payload).  To this
 * end, the message consists of the so-called parts (`#HTCore::DataPart`).
 */
class HTCore::DataMsg
{
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR
     ***************************************************************************/
public:
    /**
     * Construct empty data message (that contains no data parts)
     */
    explicit DataMsg();


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:

    /** The sequence of data parts (see `#HTCore::DataPart`)
     */
    std::vector<DataPart> data_parts;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/

public:
    /**
     * Add data of particular type.
     *
     * If the last data part has data of exactly the same type, then new data
     * is appended to the last part. Otherwise, new data part is created and
     * added to the sequence of message data parts.
     *
     * Note that if last data part is `#HTCore::DataPart::PartType::COMBINED`,
     * then new data won't be appended to it, but new part will be created
     * instead. This is because combined data parts are self-contained:
     * typically, they have some payload data, and some service data that
     * represents this payload data. If we append either data, this semantic
     * will be lost.
     */
    void addData(DataPart::DataType data_type, const std::vector<uint8_t> &data);

    /**
     * Add data byte of particular type.
     *
     * See `addData()` for details.
     */
    void addDataByte(DataPart::DataType data_type, uint8_t byte);

    /**
     * Add the whole data part. The part is always added as it is, without
     * appending data from it to the last existing part.
     */
    void addDataPart(DataPart data_part);

    /**
     * Clear all data from the message.
     */
    void clear();

    /**
     * Get user (payload) data. It is collected from all the data parts.
     */
    std::shared_ptr<std::vector<uint8_t>> getUserData() const;

    /**
     * Get service data (to be transmitted on the wire). It is collected from
     * all the data parts.
     */
    std::shared_ptr<std::vector<uint8_t>> getRawData() const;

    /**
     * Get the sequence of data parts.
     */
    std::vector<DataPart> getDataParts() const;

    /**
     * Generate human-readable string representation of the message.
     */
    std::string toString() const;

    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/


    /*******************************************************************************
     * OPERATORS
     ******************************************************************************/

public:
    inline bool operator==(const DataMsg &other) const {
        return (this->data_parts == other.data_parts);
    }
};


#endif // _HTDATAMSG_H
