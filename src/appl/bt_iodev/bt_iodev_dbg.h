/*******************************************************************************
 *   Description:   TODO
 *
 ******************************************************************************/

#ifndef _BT_IODEV_DBG_H
#define _BT_IODEV_DBG_H

/*******************************************************************************
 * INCLUDED FILES
 ******************************************************************************/


#include <cstdint>
#include <vector>

#include <QTimer>

#include "bt_iodev.h"



/*******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

class IODevDbg : public BTCore::IODev
{
Q_OBJECT
    /****************************************************************************
     * TYPES
     ***************************************************************************/

    /****************************************************************************
     * CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT
     ***************************************************************************/
public:
    explicit IODevDbg();
    virtual ~IODevDbg();

    IODevDbg(const IODevDbg &other) = delete;
    IODevDbg(IODevDbg &&other) = delete;

    IODevDbg &operator=(const IODevDbg &other) = delete;
    IODevDbg &operator=(IODevDbg &&other) = delete;


    /****************************************************************************
     * PRIVATE DATA
     ***************************************************************************/
private:
    QTimer timer;
    std::vector<uint8_t> cur_data;

    int stage;


    /****************************************************************************
     * STATIC METHODS
     ***************************************************************************/

    /****************************************************************************
     * METHODS
     ***************************************************************************/
public:

    std::vector<uint8_t> read() override;
    void write(const std::vector<uint8_t> &data) override;


    /****************************************************************************
     * SIGNALS, SLOTS
     ***************************************************************************/
signals:
    //NOTE: we should NOT define signals in subclasses,
    //      since if we do, then function pointer-based
    //      connect() syntax will not generate any errors,
    //      but it will just not work silently.
    //
    //void readyRead(int bytes_available);

private slots:
    void nextMsgGenerate();


    /****************************************************************************
     * OPERATORS
     ***************************************************************************/

};


#endif // _BT_IODEV_DBG_H
