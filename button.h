/*
 * button.h
 *
 *  Created on: Jul 25, 2018
 *      Author: matt
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "reg_access.h"
#include "msp430g2553_reg.h"

class Button
{

public:
    Button();
    bool is_button_pressed();
    void button_reset();




private:
    bool button_pressed;


};


#endif /* BUTTON_H_ */
