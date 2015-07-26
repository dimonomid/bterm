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

namespace HTCore {
   class ByteArrRead;
}

/*
 * TODO: implement the fill byte
 *       implement unit tests
 */

/**
 * TODO
 */
class HTCore::ByteArrRead : public QObject
{
Q_OBJECT
   /****************************************************************************
    * TYPES
    ***************************************************************************/

public:
   enum Endianness {
      LITTLE_END,
      BIG_END
   };

   /****************************************************************************
    * CONSTRUCTOR, DESTRUCTOR
    ***************************************************************************/
public:
   explicit ByteArrRead(const std::vector<uint8_t> &data);


   /****************************************************************************
    * PRIVATE DATA
    ***************************************************************************/
protected:

   std::shared_ptr<std::vector<uint8_t>> p_data;



   /****************************************************************************
    * STATIC METHODS
    ***************************************************************************/

   /****************************************************************************
    * METHODS
    ***************************************************************************/

public:

   std::shared_ptr<const std::vector<uint8_t>> getData() const;


public slots:

   long getU08(unsigned int index);
   long getU16(unsigned int index, int end = LITTLE_END);
   long getU32(unsigned int index, int end = LITTLE_END);

   long getS08(unsigned int index);
   long getS16(unsigned int index, int end = LITTLE_END);
   long getS32(unsigned int index, int end = LITTLE_END);



   /****************************************************************************
    * SIGNALS, SLOTS
    ***************************************************************************/

};


#endif // _BYTEARR_READ_H
