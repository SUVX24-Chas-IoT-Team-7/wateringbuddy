/**
 * @file MoistureSensor.hpp
 * @author John Collinder
 * @brief Moisture Sensor class to handle moisture sensor
 * @details This class is used to handle the moisture sensor. It reads the moisture value from the sensor
 *        It also has a method to get the raw value from the sensor
 *      It has a method to begin the sensor
 *    It has a method to read the moisture value
 * @version 0.1
 * @date 2025-03-14
 */

#ifndef MOISTURE_SENSOR_HPP
#define MOISTURE_SENSOR_HPP

class MoistureSensor
{
private:
    int powerPin;
    int sensorPin;
    int rawValue;

public:
    MoistureSensor(int powerPin, int sensorPin)
        : powerPin(powerPin), sensorPin(sensorPin), rawValue(0) {}

    void begin()
    {
        pinMode(powerPin, OUTPUT);
        pinMode(sensorPin, INPUT);
        digitalWrite(powerPin, LOW);
    }
    /**
     * @brief
     *
     * @return int
     */
    int readMoisture()
    {
        digitalWrite(powerPin, HIGH);
        delay(10);

        rawValue = analogRead(sensorPin);

        digitalWrite(powerPin, LOW);

        return rawValue;
    }

    int getRawValue() const
    {
        return rawValue;
    }
};

#endif