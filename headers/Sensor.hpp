/**
 * @file Sensor.hpp
 * @author Love Lindeborg (lindeborglove@gmail.com)
 * @brief This file handles input sensors
 * @version 0.1
 * @date 2025-03-10
 * @copyright Copyright (c) 2025
 */
#ifndef __SENSOR_CLASS_HPP__
#define __SENSOR_CLASS_HPP__

#include <stdint.h>
#include "Pin.hpp"

/**
 * @brief This class is a wrapper for the pin  sensor data
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
    virtual void read();

    /**
     * @brief Gets the data from `read()`.
     */
    int getData();

    /**
     * @brief Construct a new Sensor object
     *
     * @param pin Which pin to read data from.
     */
    Sensor(int pin, PinMode pinMode);

    // virtual ~Sensor();

    /**
     * @brief Sets the ´pin´ to INPUT using ´pinMode´
     */
    virtual void init();

protected:
    // int m_pinNumber;
    Pin m_pin;
    Pin *getPin();

    int m_data = -1;

private:
    //    Pin *m_pin;
};

#endif