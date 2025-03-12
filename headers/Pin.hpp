/**
 * @file Pin.hpp
 * @author Love Lindeborg (lindeborglove@gmail.com)
 * @brief This file handles the state of pins
 * @version 0.1
 * @date 2025-03-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __PIN_CLASS_HPP__
#define __PIN_CLASS_HPP__

#include <stdint.h>
#include <Arduino.h>

/**
 * @brief This class handles sensor input and reads sensor data
 * 
 */
class Pin 
{
public:
    /**
     * @brief Reads value from given pin as an analog value.
     * 
     * @returns value or -1 on error
     */
    const uint8_t read();

    /**
     * @brief Writes to specified pin using digitalWrite()
     * 
     * @param status High or Low (true or false)
     */
    void write(bool status);

    /**
     * @brief Writes to pin using analogWrite()
     * 
     * @param status Value between 0 - 1023
     */
    void write(int status);

    /**
     * @brief Construct a new Pin object
     * 
     * @details Sets the ´pin´ to INPUT using ´pinMode´
     * 
     * @param pin Which pin to read data from.
     */
    Pin(int pin, PinMode);

private:
    PinMode m_mode;
    uint8_t m_pin, m_data;
};

#endif