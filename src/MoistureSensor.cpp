#include "MoistureSensor.hpp"

MoistureSensor::MoistureSensor(uint8_t powerPin, uint8_t inputPin, LedPins ledPins, int thresholds[3])
    : Sensor(inputPin), m_powerPin(powerPin), m_ledPins(ledPins)
{
    this->thresholds[0] = thresholds[0];
    this->thresholds[1] = thresholds[1];
    this->thresholds[2] = thresholds[2];
}

void MoistureSensor::init() 
{
    pinMode(m_powerPin, OUTPUT);
    
    for (uint8_t *i = &m_ledPins.green; i < &m_ledPins.blue; i++) {
        pinMode(*i, OUTPUT);
    }

    pinMode(this->m_pinNumber, INPUT);
}
