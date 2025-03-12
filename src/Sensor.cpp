#include "Sensor.hpp"

#include <Arduino.h>

const uint8_t Sensor::read()
{
    this->m_data = analogRead(this->m_pin);
    return this->m_data;
}

Sensor::Sensor(int pin)
{
    this->m_pin = pin;

    pinMode(pin, INPUT);
}
