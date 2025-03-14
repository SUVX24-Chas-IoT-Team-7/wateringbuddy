/**
 * @file Buttons.hpp
 * @author Erik Dahl (erik@iunderlandet.se)
 * @brief Button class written for IoT project at Chas Academy
 * @version 0.1
 * @date 2025-03-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __IOT_BUTTON_CLASS_HPP__
#define __IOT_BUTTON_CLASS_HPP__

#include "Pin.hpp"

enum ButtonState {
    NOPRESS = 0,
    SHORTPRESS,
    LONGPRESS
};

class Button {
private:
    Pin m_pin;
    uint16_t m_lastState { 0 };
    uint16_t m_currentState { 0 };
    const time_t m_longPressTime;
    const time_t debounceTime { 50 };
    time_t m_pressTime { 0 };
    bool m_isPressed { false };
    bool m_awaitingLongpress { false };
    bool pressDetected();
    bool releaseDetected();
public:
    Button(int pin, PinMode);
    void init();
    ButtonState getState();
};



#endif