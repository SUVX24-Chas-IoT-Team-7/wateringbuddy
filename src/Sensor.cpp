#include "Sensor.hpp"
#include <Arduino.h>

Sensor::Sensor(int pin, PinMode pinMode) : m_pin(pin, pinMode) {}

// Sensor::~Sensor() 
// {
//     delete this->m_pin;
//     this->m_pin = nullptr;
// }

int Sensor::getData()
{
    return this->m_data;
}

void Sensor::read() 
{
    this->m_data = this->m_pin.read(Pin::ANALOG).value_or(0);
}

void Sensor::init() 
{
    m_pin.init();
}

Pin *Sensor::getPin() 
{
    return &(this->m_pin);
}


