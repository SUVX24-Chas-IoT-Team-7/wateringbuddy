/**
 * @file MoistureSensor.hpp
 * @author Love Lindeborg (lindeborglove@gmail.com)
 * @brief Collects information from moisture sensor on a specified pin.
 * @version 0.1
 * @date 2025-03-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __MOISTURE_SENSOR_CLASS_HPP__
#define __MOISTURE_SENSOR_CLASS_HPP__

#include <stdint.h>
#include "Pin.hpp"
#include "Sensor.hpp"

#include "ThresholdManager.hpp"

/**
 * @brief This class collects data from a moisture sensor at a specified pin.
 * 
 */
class MoistureSensor : public Sensor 
{ 
public:

   struct LedPins {
      uint8_t green, yellow, red, blue;
   };

   /**
    * @brief Construct a new MoistureSensor object
    * 
    * @param pin Which pin to read data from.
    */
   MoistureSensor(uint8_t powerPin, uint8_t inputPin, const LedPins &ledPins, ThresholdManager *thresholdManager);

   ~MoistureSensor() = default;

   /**
    * @brief Sets pin from constructor to INPUT using ´pinMode´ and 
    */
   void init() override;

   /**
    * @brief Reads data from sensor and turns on the correct LED provided in the constructor
    * 
    */
   void read() override;

   time_t getLastMeasurement();
   float getPercentage();
 
private:
   uint8_t m_powerPin;
   LedPins m_ledPins;

   float percentage = 0;

   time_t lastMeasurement;
   ThresholdManager *m_pThresholdManager = nullptr;
};
 
#endif
