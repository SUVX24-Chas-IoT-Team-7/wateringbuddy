#include "Pin.hpp"

#include <Arduino.h>

const uint16_t Pin::read(bool digital)
{
    if (this->m_mode != INPUT) return -1; 

    if (digital) this->m_data = digitalRead(this->m_pin);
    else this->m_data = analogRead(this->m_pin);
    
    return this->m_data;
}

void Pin::write(bool status)
{
    if (this->m_mode == OUTPUT)
        digitalWrite(this->m_pin, status);
}

void Pin::write(int status)
{
    if (this->m_mode == OUTPUT)
        analogWrite(this->m_pin, status);
}

Pin::Pin(int pin, PinMode mode)
{
    this->m_pin = pin;
    this->m_mode = mode;

    pinMode(pin, mode);
}
