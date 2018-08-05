/*
 * uart.cpp
 *
 *  Created on: Aug 3, 2018
 *      Author: matt
 */




#include "uart.h"

uart::uart(uint8_t id)
{
    bool_data_available = false;
    uart::handlers[id] = this;

    if(reg_access<uint16_t, uint8_t, my_msp430::reg::UCA0CTL1, my_msp430::reg::bval0>::reg_get()
            & UCSWRST){

        reg_access<uint16_t, uint8_t, my_msp430::reg::UCA0CTL1, UCSSEL_2>::reg_or();
        //104 for 16MHZ, 6 for 1MHZ
        reg_access<uint16_t, uint8_t, my_msp430::reg::UCA0BR0, 104>::reg_set();
        reg_access<uint16_t, uint8_t, my_msp430::reg::UCA0BR1, 0>::reg_set();
        reg_access<uint16_t, uint8_t, my_msp430::reg::UCA0MCTL, 0x2>::reg_set();
        reg_access<uint16_t, uint8_t, my_msp430::reg::UCA0MCTL, UCOS16>::reg_or();


        reg_access<uint16_t, uint8_t, my_msp430::reg::UCA0CTL1, UCSWRST>::reg_and_not();
        reg_access<uint16_t, uint8_t, my_msp430::reg::IE2, UCA0RXIE>::reg_or();

    }

    //Set up pins P1.1 & P1.2
    reg_access<uint16_t, uint8_t, my_msp430::reg::P1SEL, my_msp430::reg::bval1>::reg_or();
    reg_access<uint16_t, uint8_t, my_msp430::reg::P1SEL, my_msp430::reg::bval2>::reg_or();
    reg_access<uint16_t, uint8_t, my_msp430::reg::P1SEL2, my_msp430::reg::bval1>::reg_or();
    reg_access<uint16_t, uint8_t, my_msp430::reg::P1SEL2, my_msp430::reg::bval2>::reg_or();


}

void uart::handler()
{

    uart::rx_buffer.put(dynamic_access<uint16_t, uint8_t>::reg_get(my_msp430::reg::UCA0RXBUF));


}

void uart::send_data(uint8_t data)
{

    while(!(reg_access<uint16_t, uint8_t, my_msp430::reg::IFG2, my_msp430::reg::bval0>::reg_get() & UCA0TXIFG));
    dynamic_access<uint16_t, uint8_t>::reg_set(my_msp430::reg::UCA0TXBUF, data);


}

bool uart::data_available()
{
    return !uart::rx_buffer.empty();
}

uint8_t uart::get_data()
{

    return uart::rx_buffer.get();

}


#pragma INTERRUPT
__attribute__((interrupt(USCIAB0RX_VECTOR))) void rx_isr(void){
    if (IFG2 & UCA0RXIFG) {
    uart::handlers[1]->handler();
    reg_access<uint16_t, uint8_t, my_msp430::reg::IFG2, UCA0RXIFG>::reg_and_not();
    }
}


