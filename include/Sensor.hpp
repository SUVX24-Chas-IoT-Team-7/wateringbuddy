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
     * @return const uint8_t 
     */
    const uint8_t read();

    /**
     * @brief Construct a new Sensor object
     * 
     * @details Sets the ´pin´ to INPUT using ´pinMode´
     * 
     * @param pin Which pin to read data from.
     */
    Sensor(int pin);

private:

    uint8_t m_pin, m_data;

};

#endif