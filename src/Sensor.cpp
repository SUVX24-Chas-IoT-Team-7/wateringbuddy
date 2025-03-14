#include "Sensor.hpp"
#include <Arduino.h>

Sensor::Sensor(int pin) : m_pinNumber(pin)
{

}

Sensor::~Sensor() 
{
    delete this->m_pin;
    this->m_pin = nullptr;
}

int Sensor::getData()
{
    return this->m_data;
}

void Sensor::read() 
{
    this->m_data = this->m_pin->read(false);
}

void Sensor::init() 
{
    this->m_pin = new Pin(m_pinNumber, INPUT);
}

Pin *Sensor::getPin() 
{
    return this->m_pin;
}


