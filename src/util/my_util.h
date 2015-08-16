/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _MY_UTIL_H
#define _MY_UTIL_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/


#include <vector>
#include <cstdint>

#include <QString>
#include <QVariant>
#include <QJSValue>

namespace MyUtil
{
   /****************************************************************************
    * PUBLIC FUNCTIONS
    ***************************************************************************/

   QString byteArrayToHex(const std::vector<uint8_t> &data);
   QVariantMap qjsErrorToVariant(const QJSValue &valError);

};


#endif // _MY_UTIL_H
