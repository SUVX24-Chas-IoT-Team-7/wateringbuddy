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
        digitalWrite(powerPin, LOW); // Start with sensor off
    }

    int readMoisture()
    {
        // Apply power to the sensor
        digitalWrite(powerPin, HIGH);
        delay(10); // Wait for sensor to stabilize

        // Read the value
        rawValue = analogRead(sensorPin);

        // Turn off power to reduce corrosion
        digitalWrite(powerPin, LOW);

        return rawValue;
    }

    int getRawValue() const
    {
        return rawValue;
    }
};

#endif