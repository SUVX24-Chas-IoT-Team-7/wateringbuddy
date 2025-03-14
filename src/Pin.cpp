#include "Pin.hpp"

#include <Arduino.h>

const std::optional<uint16_t> Pin::read(bool digital)
{
    if (this->m_mode != INPUT) return {}; 
  
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

void Pin::init() {
    pinMode(m_pin, m_mode);
}

Pin::Pin(int pin, PinMode mode) : m_pin { pin }, m_mode { mode } {}
