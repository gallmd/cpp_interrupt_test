/*
 * msp430g2553_reg.h
 *
 *  Created on: Jul 5, 2018
 *      Author: matt
 */

#ifndef MSP430G2553_REG_H_
#define MSP430G2553_REG_H_



#include <stdint.h>

namespace my_msp430
{

    namespace reg
    {

        // Bit-position values.
        constexpr uint8_t bval0  = 1U;
        constexpr uint8_t bval1  = 1U << 1U;
        constexpr uint8_t bval2  = 1U << 2U;
        constexpr uint8_t bval3  = 1U << 3U;
        constexpr uint8_t bval4  = 1U << 4U;
        constexpr uint8_t bval5  = 1U << 5U;
        constexpr uint8_t bval6  = 1U << 6U;
        constexpr uint8_t bval7  = 1U << 7U;

        //clock values
        constexpr uint8_t CALBC1_16MHZ = 0x8F;
        constexpr uint8_t CALDCO_16MHZ = 0xAA;

        //ports
        constexpr uint16_t P1IN = 0x0020U;
        constexpr uint16_t P1OUT = 0x0021U;
        constexpr uint16_t P1DIR = 0x0022U;
        constexpr uint16_t P1SEL = 0x0026U;
        constexpr uint16_t P1IES = 0x0024U;
        constexpr uint16_t P1IE = 0x0025U;
        constexpr uint16_t P1SEL2 = 0x0041U;
        constexpr uint16_t P1REN = 0x0027U;



        constexpr uint16_t P2IN = 0x0028U;
        constexpr uint16_t P2OUT = 0x0029U;
        constexpr uint16_t P2DIR = 0x002AU;
        constexpr uint16_t P2SEL = 0x002EU;

        constexpr uint16_t P3IN = 0x0018U;
        constexpr uint16_t P3OUT = 0x0019U;
        constexpr uint16_t P3DIR = 0x001AU;
        constexpr uint16_t P3SEL = 0x001BU;

        //watchdog timer
        constexpr uint16_t WDTCTL = 0x0120;

        //clock
        constexpr uint16_t DCOCTL = 0x0056;
        constexpr uint16_t BCSCTL1 = 0x0057;

        //Communication
        constexpr uint16_t UCB0CTL1 = 0x0069U;
        constexpr uint16_t UCB0CTL0 = 0x0068U;
        constexpr uint16_t UCB0BR0 = 0x006AU;
        constexpr uint16_t UCB0BR1 = 0x006BU;
        constexpr uint16_t UCB0I2CSA = 0x011AU;
        constexpr uint16_t UCB0STAT = 0x006DU;
        constexpr uint16_t UCB0TXBUF = 0x006FU;
        //constexpr uint8_t UCB0TXIE = 0x08U;
        //constexpr uint8_t UCSWRST = 0x01U;
        //constexpr uint8_t UCSSEL_2 = 0x80U;
        //constexpr uint8_t UCMST = 0x08U;
        //constexpr uint8_t UCMODE_3 = 0x06U;
        //constexpr uint8_t UCSYNC = 0x01U;

        //interrupts
        constexpr uint16_t IE1 = 0x0000U;
        constexpr uint16_t IFG1 = 0x0002U;
        constexpr uint16_t IE2 = 0x0001U;
        constexpr uint16_t IFG2 = 0x0003U;



        }


    }








#endif /* MSP430G2553_REG_H_ */
