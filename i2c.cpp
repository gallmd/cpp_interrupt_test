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

int8_t i2c::send_data(uint8_t address, send_buffer send_buf)
{
    int8_t err = 0;

    //0x70 for display
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0I2CSA, 0x070U>::reg_set();

    //send start condition
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, (UCTR | UCTXSTT)>::reg_or();

    //Wait for the start condition to be sent and ready to transmit interrupt
    while((dynamic_access<uint16_t, uint8_t>::reg_get(my_msp430::reg::UCB0CTL1) & UCTXSTT) && ((dynamic_access<uint16_t, uint8_t>::reg_get(my_msp430::reg::IFG2) &  UCB0TXIFG) ==0));

    err = i2c::check_ack();
    if(err >= 0){

    for(auto it = send_buf.begin(); it != send_buf.end(); ++it){

        dynamic_access<uint16_t, uint8_t>::reg_set(my_msp430::reg::UCB0TXBUF, *it);
        while((reg_access<uint16_t, uint8_t, my_msp430::reg::IFG2, my_msp430::reg::bval0>::reg_get() & UCB0TXIFG)==0){

            err = i2c::check_ack();
            if(err < 0){
                break;
            }
        }

    }
    }


    //send stop
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, UCTXSTP>::reg_or();

    return err;

}

int8_t i2c::check_ack(){

    if(dynamic_access<uint16_t, uint8_t>::reg_get(my_msp430::reg::UCB0STAT) & UCNACKIFG){
            //Stop I2C Transmission
            dynamic_access<uint16_t, uint8_t>::reg_or(my_msp430::reg::UCB0CTL1, UCTXSTP);

            //clear interrupt flag) &  UCB0TXIFG) ==0));

            dynamic_access<uint16_t, uint8_t>::reg_not(my_msp430::reg::UCB0STAT, UCNACKIFG);

            return -1;
    }

    return 0;
}


