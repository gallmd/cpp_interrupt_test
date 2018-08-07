/*
 * i2c.cpp
 *
 *  Created on: Jul 30, 2018
 *      Author: matt
 */


#include "i2c.h"

i2c::i2c(uint8_t id)
{

    i2c::handlers[id] = this;
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

int8_t i2c::send_data(uint8_t address, send_buffer_type send_buf)
{
    int8_t err = 0;

    //0x70 for display
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0I2CSA, 0x070U>::reg_set();

    //fill out circular buffer for TX interrupt to use...make this better
    i2c::send_data_size = send_buf.size();
    for(auto it = send_buf.begin(); it != send_buf.end(); ++it)
    {

        i2c::send_buffer.put(*it);

    }

    //send start condition, let interrupt send data
    reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, (UCTR | UCTXSTT)>::reg_or();


    return err;

}

void i2c::handler()
{

    if(!i2c::send_buffer.empty()){
        dynamic_access<uint16_t, uint8_t>::reg_set(my_msp430::reg::UCB0TXBUF, i2c::send_buffer.get());
    }else{

        //no more data to send, send stop and clear interrupt
        reg_access<uint16_t, uint8_t, my_msp430::reg::UCB0CTL1, UCTXSTP>::reg_or();
        reg_access<uint16_t, uint8_t, my_msp430::reg::IFG2, UCB0TXIFG>::reg_and_not();

    }


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

#pragma INTERRUPT
__attribute__((interrupt(USCIAB0TX_VECTOR))) void USCIAB0TX_ISR(void){
    if (IFG2 & UCB0TXIFG) {
    i2c::handlers[1]->handler();
    }
}
