#include "MoistureSensor.hpp"

MoistureSensor::MoistureSensor(uint8_t powerPin, uint8_t inputPin, const LedPins &ledPins, ThresholdManager *thresholdManager)
    : Sensor(inputPin, INPUT), m_powerPin(powerPin), m_ledPins(ledPins), m_pThresholdManager(thresholdManager)
{
    
}

void MoistureSensor::init() 
{
    Sensor::init();
    
    pinMode(m_powerPin, OUTPUT);
    
    pinMode(this->m_ledPins.blue, OUTPUT);
    pinMode(this->m_ledPins.red, OUTPUT);
    pinMode(this->m_ledPins.yellow, OUTPUT);
    pinMode(this->m_ledPins.green, OUTPUT);

    // for (uint8_t *i = &m_ledPins.green; i < &m_ledPins.blue; i++) {
    //     pinMode(*i, OUTPUT);
    // }
}

void MoistureSensor::read() {
    digitalWrite(m_powerPin, HIGH);
    delay(10); // Give the sensor time to power on

    digitalWrite(this->m_ledPins.blue, LOW);
    digitalWrite(this->m_ledPins.red, LOW);
    digitalWrite(this->m_ledPins.yellow, LOW);
    digitalWrite(this->m_ledPins.green, LOW);

    this->m_data = getPin()->read(Pin::ANALOG).value_or(0);
    this->percentage = map(this->m_data, 1, 1023, 100, 0);
    this->lastMeasurement = millis();

    digitalWrite(m_pThresholdManager->getLEDPin(percentage), HIGH);
    digitalWrite(m_powerPin, LOW);
}

time_t MoistureSensor::getLastMeasurement()
{
    return this->lastMeasurement;
}

float MoistureSensor::getPercentage()
{
    return this->percentage;
}
