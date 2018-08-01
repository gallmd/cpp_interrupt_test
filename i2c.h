/*
 * i2c.h
 *
 *  Created on: Jul 30, 2018
 *      Author: matt
 */

#ifndef I2C_H_
#define I2C_H_

#include "msp430g2553_reg.h"
#include "msp430.h"
#include "reg_access.h"
#include "reg_access_dynamic.h"
#include "util_circular_buffer.h"
#include <cstdint>
#include <array>

class i2c
{

public:
    typedef std::array<uint8_t, 17>send_buffer;


    i2c();
    int8_t send_data(uint8_t address, send_buffer send_buf);

private:

    int8_t check_ack();



};



#endif /* I2C_H_ */
