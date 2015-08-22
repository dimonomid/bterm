/******************************************************************************
 *   Description:   See class declaration in header file
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htdatapart.h"

#include <vector>
#include <stdexcept>


using namespace std;
using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

DataPart::DataPart() :
    service_data(),
    user_data()
{
}

DataPart::DataPart(DataPart::DataType data_type, const vector<uint8_t> &data) :
    service_data(data_type == DataType::SERVICE ? data : std::vector<uint8_t>{}),
    user_data   (data_type == DataType::USER    ? data : std::vector<uint8_t>{})
{
}

DataPart::DataPart(DataPart::DataType data_type, vector<uint8_t> &&data) :
    service_data(data_type == DataType::SERVICE ? data : std::vector<uint8_t>{}),
    user_data   (data_type == DataType::USER    ? data : std::vector<uint8_t>{})
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

void DataPart::addData(DataType data_type, const vector<uint8_t> &data)
{
    switch (data_type){
        case DataPart::DataType::SERVICE:
            this->service_data.insert(
                    this->service_data.end(),
                    data.cbegin(), data.cend()
                    );
            break;
        case DataPart::DataType::USER:
            this->user_data.insert(
                    this->user_data.end(),
                    data.cbegin(), data.cend()
                    );
            break;
    }
}

void DataPart::addDataByte(DataType data_type, uint8_t byte)
{
    switch (data_type){
        case DataPart::DataType::SERVICE:
            this->service_data.push_back(byte);
            break;
        case DataPart::DataType::USER:
            this->user_data.push_back(byte);
            break;
    }
}



vector<uint8_t> DataPart::getData(DataPart::DataType data_type) const
{
    vector<uint8_t> ret;

    switch (data_type){
        case DataPart::DataType::SERVICE:
            ret = this->service_data;
            break;
        case DataPart::DataType::USER:
            ret = this->user_data;
            break;
    }

    return ret;
}


DataPart::PartType DataPart::getType() const
{
    DataPart::PartType ret;

    //-- determine part type depending on contained data type
    if (user_data.size() != 0 && service_data.size() == 0){
        ret = DataPart::PartType::USER;
    } else if (user_data.size() == 0 && service_data.size() != 0){
        ret = DataPart::PartType::SERVICE;
    } else if (user_data.size() != 0 && service_data.size() != 0){
        ret = DataPart::PartType::COMBINED;
    } else {
        ret = DataPart::PartType::EMPTY;
    }

    return ret;
}

bool DataPart::canDataBeAddedHomogeneously(DataPart::DataType data_type) const
{
    DataPart::PartType part_type = this->getType();

    return (
            part_type == DataPart::PartType::EMPTY
            ||
            (data_type == DataPart::DataType::SERVICE && part_type == DataPart::PartType::SERVICE)
            ||
            (data_type == DataPart::DataType::USER    && part_type == DataPart::PartType::USER)
           );
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */


