/**
 * @file Sensor.hpp
 * @author Love Lindeborg (lindeborglove@gmail.com)
 * @brief This file handles input sensors
 * @version 0.1
 * @date 2025-03-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __STORAGE_CLASS__
#define __STORAGE_CLASS__

#include <stdint.h>

/**
 * @brief This class handles sensor input and reads sensor data
 * 
 */
class Sensor 
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
    void Sensor::write(bool status);

    /**
     * @brief Writes to pin using analogWrite()
     * 
     * @param status Value between 0 - 1023
     */
    void Sensor::write(int status);

    /**
     * @brief Construct a new Sensor object
     * 
     * @details Sets the ´pin´ to INPUT using ´pinMode´
     * 
     * @param pin Which pin to read data from.
     */
    Sensor(int pin, PinMode);

private:
    PinMode m_mode;
    uint8_t m_pin, m_data;
};

#endif