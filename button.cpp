/*
 * button.cpp
 *
 *  Created on: Jul 25, 2018
 *      Author: matt
 */



#include "button.h"


Button::Button(uint8_t id)
{
    button_pressed = false;
    Button::handlers[id] = this;
    //hard code for P1.3, set as input, enable interrupt
    reg_access<uint8_t, uint8_t, my_msp430::reg::P1DIR, my_msp430::reg::bval3>::reg_and_not();
    reg_access<uint8_t, uint8_t, my_msp430::reg::P1SEL, my_msp430::reg::bval3>::reg_and_not();
    reg_access<uint8_t, uint8_t, my_msp430::reg::P1SEL2, my_msp430::reg::bval3>::reg_and_not();
    reg_access<uint8_t, uint8_t, my_msp430::reg::P1REN, my_msp430::reg::bval3>::reg_or();

    reg_access<uint8_t, uint8_t, my_msp430::reg::P1IES, my_msp430::reg::bval3>::reg_or();
    reg_access<uint8_t, uint8_t, my_msp430::reg::P1IE, my_msp430::reg::bval3>::reg_or();




}

bool Button::is_button_pressed()
{

    return button_pressed;

}

void Button::button_reset()
{

    button_pressed = false;

}

void Button::handler(){

    button_pressed = true;
}



