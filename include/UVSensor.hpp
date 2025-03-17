#ifndef UV_SENSOR_HPP
#define UV_SENSOR_HPP
/**
 * @brief
 * UVSensor class to handle UV sensor
 * @details
 * This class is used to handle UV sensor. It reads the UV index value from the sensor
 * It has a method to begin the sensor
 * It has a method to read the UV index value
 * @version 0.1
 * @date 2025-03-14
 *
 */
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
        int rawValue = analogRead(sensorPin);

        float voltage = rawValue * (5.0 / 1023.0);

        uvIndex = round(voltage * 10);

        return uvIndex;
    }
};

#endif