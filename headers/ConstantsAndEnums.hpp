#ifndef MOIST_CONSTANTS_AND_ENUMS_HPP
#define MOIST_CONSTANTS_AND_ENUMS_HPP
/**
 * @file ConstantsAndEnums.hpp
 * @author Erik Dahl (you@domain.com)
 * @brief  Constants and enums for the project
 * @details This file contains all the constants and enums used in the project
 * @version 0.1
 * @date 2025-03-20
 */
#include <Arduino.h>

enum thresholdNames
{
  DRY,
  GOOD,
  WET
};

namespace moisture
{
  /**
   * @brief  Moisture sensor pins
   */
  const int powerPin = A0;
  const int readingPin = A1;
  /**
   * @brief  LED pins
   */
  const int redPin = 6;
  const int yellowPin = 7;
  const int greenPin = 8;
  const int bluePin = 9;
  const int ledPins[] = {redPin, yellowPin, greenPin, bluePin};

} // moisture

/**
 * @brief  light and UV sensor pins
 */
namespace lightSensors
{
  const int lightReadingPin = A2;
  const int uvReadingPin = A3;
} // lightSensors


/**
 * @brief   Display modes for the LCD
 */
enum DisplayMode
{
  UPDATE_DISPLAY,
  MOISTURE_DISPLAY,
  LIGHT_DISPLAY,
  MOISTURE_TRESHOLD_DISPLAY,
  WATERING_DISPLAY,
  ADJUST_MOISTURE_DISPLAY,
  LIGHT_FASTMODE_DISPLAY
};

/**
 * @brief  Push button pins
 */
namespace pushButtons {
   const int TglPin = 2;
   const int DecrPin = 3;
   const int IncrPin = 4;
}

#endif