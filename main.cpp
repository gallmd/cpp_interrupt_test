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
#include "i2c.h"
#include "uart.h"
#include <array>


Button* Button::handlers[2] = {0};
Button my_btn(1);

uart* uart::handlers[2] = {0};
uart my_uart(1);



int main()
{

    WDTCTL = WDTPW + WDTHOLD;
    my_uart.data_available();


    //set clock to 16MHZ
    reg_access<uint16_t, uint8_t, my_msp430::reg::DCOCTL, 0>::reg_set();
    reg_access<uint16_t, uint16_t, my_msp430::reg::BCSCTL1, my_msp430::reg::CALBC1_16MHZ>::reg_set();
    reg_access<uint16_t, uint16_t, my_msp430::reg::DCOCTL, my_msp430::reg::CALDCO_16MHZ>::reg_set();



    /* Configure ACLK to be sourced from VLO = ~12KHz */
    BCSCTL3 |= LFXT1S_2;

    //Setup Leds
    const Led<uint16_t, uint8_t, my_msp430::reg::P1OUT, my_msp430::reg::bval0>red;
    const Led<uint16_t, uint8_t, my_msp430::reg::P1OUT, my_msp430::reg::bval6>green;

//    i2c i2c_comm;
//    const std::array<uint8_t, 17> osc_on = {0x21, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//    i2c_comm.send_data(0x070, osc_on);
//
//    const std::array<uint8_t, 17> no_blink = {0x81, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//    i2c_comm.send_data(0x70, no_blink);
//
//    const std::array<uint8_t, 17> brightness = {0xEF, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//    i2c_comm.send_data(0x70, brightness);
//
//
//    const std::array<uint8_t, 17> all_on = {0x00, 0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00};
//    i2c_comm.send_data(0x70, all_on);

//    const std::array<uint8_t, 17> all_off = {0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    //i2c_comm.send_data(0x70, all_off);




    __enable_interrupt();


    while(1){


        if(my_uart.data_available()){
            red.toggle();
        }

        if(my_btn.is_button_pressed()){

            red.toggle();
            green.toggle();
            __delay_cycles(1000000);
            my_btn.button_reset();

        }


    }


}





