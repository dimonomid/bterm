/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _TEST_HELPERS_H
#define _TEST_HELPERS_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/

#include <QtTest/QtTest>

#include <vector>


namespace QTest {
    template<>
        char *toString(const std::vector<uint8_t> &vec)
        {
            bool empty = true;
            QByteArray ba = "vector{";

            for (int byte : vec){
                if (!empty){
                    ba += ", ";
                }

                ba += "" + QByteArray::number(byte) + "";

                empty = false;
            }

            ba += "}";
            return qstrdup(ba.data());
        }
}


#endif // _TEST_HELPERS_H

