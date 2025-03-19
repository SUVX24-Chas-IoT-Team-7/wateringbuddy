#ifndef MOIST_CONSTANTS_AND_ENUMS_HPP
#define MOIST_CONSTANTS_AND_ENUMS_HPP

#include <Arduino.h>

enum thresholdNames
{
  DRY,
  GOOD,
  WET
};

namespace moisture
{
  // sensor pins
  const int powerPin = A0;
  const int readingPin = A1;
  // LED pins
  const int redPin = 6;
  const int yellowPin = 7;
  const int greenPin = 8;
  const int bluePin = 9;
  const int ledPins[] = {redPin, yellowPin, greenPin, bluePin};

} // moisture

namespace uvsensor
{
  const int readingPin = A2;

} // uvsensor

  enum DisplayMode
  {
    MOISTURE_DISPLAY,
    LIGHT_DISPLAY,
    MOISTURE_TRESHOLD_DISPLAY,
    WATERING_DISPLAY,
    ADJUST_MOISTURE_DISPLAY
  };

#endif