/*
 * main.cpp
 *
 *  Created on: Jul 25, 2018
 *      Author: matt
 */


#include "reg_access.h"
#include "msp430.h"
#include "msp430g2553_reg.h"
#include "led.h"
#include "button.h"

Button* Button::handlers[2] = {0};
Button my_btn(1);

#pragma INTERRUPT
__attribute__((interrupt(PORT1_VECTOR))) void port1_isr(void){

    if(P1IFG & my_msp430::reg::bval3)
    {
//    reg_access<uint16_t, uint8_t, my_msp430::reg::P1OUT, my_msp430::reg::bval0>::reg_xor();
        Button::handlers[1]->handler();
        __delay_cycles(100000);
    }

    P1IFG = 0;

}

int main()
{

    WDTCTL = WDTPW + WDTHOLD;

    //set clock to 16MHZ
    reg_access<uint16_t, uint8_t, my_msp430::reg::DCOCTL, 0>::reg_set();
    reg_access<uint16_t, uint8_t, my_msp430::reg::BCSCTL1, my_msp430::reg::CALBC1_16MHZ>::reg_set();
    reg_access<uint16_t, uint8_t, my_msp430::reg::DCOCTL, my_msp430::reg::CALDCO_16MHZ>::reg_set();

    /* Configure ACLK to be sourced from VLO = ~12KHz */
    BCSCTL3 |= LFXT1S_2;

    //Setup Leds
    const Led<uint16_t, uint8_t, my_msp430::reg::P1OUT, my_msp430::reg::bval0>red;
    const Led<uint16_t, uint8_t, my_msp430::reg::P1OUT, my_msp430::reg::bval6>green;


    __enable_interrupt();


    while(1){

        if(my_btn.is_button_pressed()){

            red.toggle();
            green.toggle();
//            __delay_cycles(1000000);
            my_btn.button_reset();

        }


    }


}

