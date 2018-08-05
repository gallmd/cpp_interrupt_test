/*
 * uart.h
 *
 *  Created on: Aug 3, 2018
 *      Author: matt
 */

#ifndef UART_H_
#define UART_H_

#include <array>
#include <cstdint>
#include "msp430g2553_reg.h"
#include "msp430.h"
#include "util_circular_buffer.h"
#include "reg_access.h"
#include "reg_access_dynamic.h"


    class uart
    {
        typedef std::array<uint8_t, 8>data_packet;

    public:
        uart(uint8_t id);
        void send_data(uint8_t data);
        void handler();
        bool data_available();
        uint8_t get_data();
        uint16_t get_buffer_address();

        static uart* handlers[2];



    private:
        util::circular_buffer<uint8_t> tx_buffer;
        util::circular_buffer<uint8_t> rx_buffer;
        bool bool_data_available;


    };


#endif /* UART_H_ */
