#include <Arduino.h>
#include "Sensor.hpp"

Sensor humidity{ A0, INPUT };

void setup() {
    uint8_t value = humidity.read();
}

void loop() {

}