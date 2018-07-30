/*
 * led.h
 *
 *  Created on: Jul 5, 2018
 *      Author: matt
 */

#ifndef LED_H_
#define LED_H_


#include <stdint.h>
#include "reg_access.h"


template<typename addr_type, typename reg_type, const addr_type port_out, const reg_type bpos>
class Led{

public:


    Led()
    {

        reg_access<addr_type, reg_type, port_out, bpos>::reg_and_not();
        reg_access<addr_type, reg_type, pdir, bpos>::reg_or();
        reg_access<addr_type, reg_type, psel, bpos>::reg_and_not();
        reg_access<addr_type, reg_type, psel2, bpos>::reg_and_not();
    }

    void toggle() const
    {

        reg_access<addr_type, reg_type, port_out, bpos>::reg_xor();

    }


private:

    static constexpr addr_type pdir = port_out + 1U;
    static constexpr addr_type psel = port_out + 5U;
    static constexpr addr_type psel2 = port_out + 20U;

};


#endif /* LED_H_ */
