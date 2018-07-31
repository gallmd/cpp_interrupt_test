/*
 * i2c.cpp
 *
 *  Created on: Jul 30, 2018
 *      Author: matt
 */


#include "i2c.h"

i2c::i2c()
{

    //Set pins 1.6 and 1.7 to i2c
    reg_access<uint16_t, uint8_t, my_msp430::reg::P1SEL, my_msp430::reg::bval6>::reg_or();
    reg_access<uint16_t, uint8_t, my_msp430::reg::P1SEL, my_msp430::reg::bval7>::reg_or();
    reg_access<uint16_t, uint8_t, my_msp430::reg::P1SEL2, my_msp430::reg::bval6>::reg_or();
    reg_access<uint16_t, uint8_t, my_msp430::reg::P1SEL2, my_msp430::reg::bval7>::reg_or();

    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, UCSWRST>::reg_or();
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL0, (UCMST+UCMODE_3+UCSYNC)>::reg_set();
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, (UCSSEL_2+UCSWRST)>::reg_set();
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0BR0, (0x0CU)>::reg_set();
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0BR1, 0>::reg_set();

    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, UCSWRST>::reg_and_not();
    reg_access<uint16_t, uint8_t, my_msp430::reg::IE2, UCB0TXIE>::reg_or();


}

void i2c::send_data(uint8_t address, send_buffer send_buf)
{
    //0x70 for display
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0I2CSA, address>::reg_set();

    //send start condition
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, (UCTR | UCTXSTT)>::reg_or();


    //send stop
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, UCTXSTP>::reg_or();

}


