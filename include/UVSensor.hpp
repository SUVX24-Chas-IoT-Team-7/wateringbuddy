#ifndef UV_SENSOR_HPP
#define UV_SENSOR_HPP

class UVSensor
{
private:
    int sensorPin;
    int uvIndex;

public:
    UVSensor(int sensorPin) : sensorPin(sensorPin), uvIndex(0) {}

    void begin()
    {
        pinMode(sensorPin, INPUT);
    }

    int readUVIndex()
    {
        // Read raw analog value
        int rawValue = analogRead(sensorPin);

        // Convert to voltage (0-5V)
        float voltage = rawValue * (5.0 / 1023.0);

        // Convert to UV index (may need calibration for your specific sensor)
        uvIndex = round(voltage * 10); // Simplified conversion

        return uvIndex;
    }
};

#endif