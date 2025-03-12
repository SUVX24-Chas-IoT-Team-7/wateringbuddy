#include <Arduino.h>
#include "Pin.hpp"

Pin humidity{ A0, INPUT };

void setup() {
    uint8_t value = humidity.read();
}

void loop() {

}