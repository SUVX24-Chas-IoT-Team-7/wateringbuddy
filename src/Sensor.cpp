#include "Sensor.hpp"

#include <Arduino.h>

const uint8_t Sensor::read()
{
    if (this->m_mode != INPUT) return -1; 
    this->m_data = analogRead(this->m_pin);
    return this->m_data;
}

void Sensor::write(bool status)
{
    if (this->m_mode == OUTPUT)
        digitalWrite(this->m_pin, status);
}

void Sensor::write(int status)
{
    if (this->m_mode == OUTPUT)
        analogWrite(this->m_pin, status);
}

Sensor::Sensor(int pin, PinMode mode)
{
    this->m_pin = pin;
    this->m_mode = mode;

    pinMode(pin, mode);
}
