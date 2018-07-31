/*
 * buffer.h
 *
 *  Created on: Mar 24, 2018
 *      Author: matt
 */

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include<array>
#include<iostream>
#include<cstdint>
namespace util{
template<typename buffer_type> class circular_buffer{


public:

    circular_buffer(){

        head = 0;
        tail = 0;
    }

    void put(buffer_type value){

        buf[head] = value;
        head =(head + 1) % buf.size();

        if(head == tail)
        {

            tail = (tail + 1) % buf.size();

        }
    }

    buffer_type get(void){

        buffer_type value = buf[tail];
        tail = (tail + 1) % buf.size();
        return value;

    }

    int buffer_size()
    {

        return buf.size();
    }

    bool full(void)
    {

        return ((head + 1) % buf.size()) == tail;

    }

    void reset(void)
    {

        head = tail;

    }



private:
    std::array<buffer_type, 4U> buf;

    std::uint8_t head;
    std::uint8_t tail;

};

}

#endif /* BUFFER_H_ */
