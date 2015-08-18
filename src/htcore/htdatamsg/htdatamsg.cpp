/******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

/******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include "htdatamsg.h"


#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace HTCore;

/*******************************************************************************
 * CONSTRUCTOR, DESTRUCTOR
 ******************************************************************************/

DataMsg::DataMsg() :
    data_parts()
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

void DataMsg::addData(DataPart::DataType data_type, uint8_t byte)
{
    if (this->data_parts.size() > 0 && this->data_parts.back().canDataBeAddedHomogeneously(data_type)){
        //-- type of new data is the same as previously added data, so, just
        //   append it to last data part

        this->data_parts.back().addData(data_type, byte);
    } else {
        //-- type of new data differs from that of previously added data
        //   (or we haven't any data yet), so, add new data part

        auto data = vector<uint8_t>();
        data.push_back(byte);

        this->data_parts.push_back(
                DataPart(data_type, data)
                );
    }
}

void DataMsg::addData(DataPart::DataType data_type, const vector<uint8_t> &data)
{
    if (this->data_parts.size() > 0 && this->data_parts.back().canDataBeAddedHomogeneously(data_type)){
        //-- type of new data is the same as previously added data, so, just
        //   append it to last data part

        this->data_parts.back().addData(data_type, data);
    } else {
        //-- type of new data differs from that of previously added data
        //   (or we haven't any data yet), so, add new data part

        this->data_parts.push_back(
                DataPart(data_type, data)
                );
    }

}

void DataMsg::addData(DataPart data_part)
{
    this->data_parts.push_back(data_part);
}

void DataMsg::clear()
{
    this->data_parts.clear();
}

std::string DataMsg::toString() const {

    std::stringstream ss{};

    for (auto data_part : this->data_parts){

        switch (data_part.getType()){

            case DataPart::PartType::SERVICE:
            case DataPart::PartType::COMBINED:
                for (int byte : data_part.getData(DataPart::DataType::SERVICE)){
                    ss << "*0x" << std::hex << byte << "*, ";
                }
                break;

            case DataPart::PartType::USER:
                for (int byte : data_part.getData(DataPart::DataType::USER)){
                    ss << "0x" << std::hex << byte << ", ";
                }
                break;

            case DataPart::PartType::EMPTY:
                //-- do nothing
                break;

            default:
                std::cerr << "wrong data_part.type";
                exit(1);
                break;
        }

    }

    return ss.str();

    //return "data parts cnt=" + std::to_string(this->data_parts.size());
}

std::shared_ptr<vector<uint8_t>> DataMsg::getUserData() const
{
    auto p_ret = std::make_shared<vector<uint8_t>>();

    for (auto data_part : this->data_parts){
        vector<uint8_t> user_data_part = data_part.getData(DataPart::DataType::USER);
        p_ret->insert(
                p_ret->end(),
                user_data_part.cbegin(), user_data_part.cend()
                );
    }

    return p_ret;
}

std::shared_ptr<vector<uint8_t>> DataMsg::getRawData() const
{
    auto p_ret = std::make_shared<vector<uint8_t>>();

    for (auto data_part : this->data_parts){
        vector<uint8_t> data_part_vector = data_part.getData(DataPart::DataType::SERVICE);
        if (data_part_vector.size() == 0){
            data_part_vector = data_part.getData(DataPart::DataType::USER);
        }
        p_ret->insert(
                p_ret->end(),
                data_part_vector.cbegin(), data_part_vector.cend()
                );
    }

    return p_ret;
}

vector<DataPart> DataMsg::getDataParts() const
{
    return data_parts;
}

/*******************************************************************************
 * SLOTS
 ******************************************************************************/

/* private      */

/* protected    */

/* public       */




