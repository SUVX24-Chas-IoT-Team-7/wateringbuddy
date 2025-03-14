/**
 * @file Pin.hpp
 * @author Love Lindeborg (lindeborglove@gmail.com) & Erik Dahl (erik@iunderlandet.se)
 * @brief This file handles the state of pins
 * @version 0.2
 * @date 2025-03-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __PIN_CLASS_HPP__
#define __PIN_CLASS_HPP__

#include <stdint.h>
#include <Arduino.h>
#include <optional>

/**
 * @brief This class handles sensor input and reads sensor data
 * 
 */
class Pin 
{
public:
    enum ReadType { ANALOG, DIGITAL };

    /**
     * @brief Reads value from given pin as an analog value.
     * 
     * @returns std::optional which is empty on error
     * Remember to check before calling value() on the returned result
     */
    const std::optional<uint16_t> read(ReadType readType);

    /**
     * @brief Writes to pin using digitalWrite()
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
     * @brief Sets the ´pin´ to INPUT/OUTPUT using ´pinMode´
     * 
     * To be called by users of class in setup() 
     */
    void init();

    /**
     * @brief Construct a new Pin object
     * 
     * @param pin Which pin to read data from.
     * @param PinMode If set to INPUT or OUTPUT
     */
    Pin(int pin, PinMode);

private:
    PinMode m_mode;
    uint8_t m_pin;
};

#endif