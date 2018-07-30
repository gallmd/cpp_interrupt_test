/*
 * button.h
 *
 *  Created on: Jul 25, 2018
 *      Author: matt
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "msp430.h"
#include "reg_access.h"
#include "msp430g2553_reg.h"

class Button
{

public:
    Button(uint8_t id);
    bool is_button_pressed();
    void button_reset();
    void handler();

    static Button* handlers[2];





private:
    bool button_pressed;


};


#endif /* BUTTON_H_ */
