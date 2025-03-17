
/**
 * @file mainWithHeaders.cpp
 *
 * @brief   Main file to run the project
 * @details This file is used to run the project. It reads the moisture and UV index values from the sensors and displays them on the LCD display
 *          It also reads the button inputs to switch between modes, select thresholds and adjust thresholds
 *        It also adjusts the LED lights based on the moisture and UV index values
 *
 * @version 0.1
 * @date 2025-03-14
 *
 *
 *
 */

#include "../include/LCDDisplay.hpp"
#include "../include/MoistureSensor.hpp"
#include "../include/UVSensor.hpp"
#include "../include/ButtonHandler.hpp"
#include <Arduino.h>
#include "../include/ThreshholdManager.hpp"

LCDDisplay display;
MoistureSensor moistureSensor(A0, A1);
UVSensor uvSensor(A2);
ButtonHandler buttons(2, 3, 4, 5);
ThresholdManager thresholds;

int displayMode = 0;

void setup()
{
  display.begin();
  moistureSensor.begin();
  uvSensor.begin();
  buttons.begin();

  for (int pin = 8; pin <= 12; pin++)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  display.showTitle("Soil Moisture");

  Serial.begin(9600);
}

void loop()
{
  int moisture = moistureSensor.readMoisture();
  int uvIndex = uvSensor.readUVIndex();

  Serial.print("Moisture = ");
  Serial.print(moisture);
  Serial.print(", UV Index = ");
  Serial.println(uvIndex);

  if (buttons.isModePressed())
  {
    if (thresholds.getMode() == 1)
    {
      thresholds.toggleMode();
      display.clear();

      if (displayMode == 0)
      {
        display.showTitle("Soil Moisture");
      }
      else
      {
        display.showTitle("UV Index");
      }
    }
    else
    {
      displayMode = !displayMode;
      display.clear();

      if (displayMode == 0)
      {
        display.showTitle("Soil Moisture");
      }
      else
      {
        display.showTitle("UV Index");
      }
    }
  }

  if (displayMode == 0 && buttons.isSelectPressed() && thresholds.getMode() == 0)
  {
    thresholds.toggleMode();
    display.clear();
    display.showTitle("Adjust Thresholds");
  }

  if (thresholds.getMode() == 1)
  {
    if (buttons.isSelectPressed())
    {
      thresholds.nextThreshold();
    }

    if (buttons.isUpPressed())
    {
      thresholds.increaseThreshold(10);
    }

    if (buttons.isDownPressed())
    {
      thresholds.decreaseThreshold(10);
    }

    display.showTitle(thresholds.getCurrentThresholdName());
    display.showValue(thresholds.getCurrentThresholdValue());
  }
  else
  {
    for (int pin = 8; pin <= 12; pin++)
    {
      digitalWrite(pin, LOW);
    }

    if (displayMode == 0)
    {
      display.showValue(moisture);

      const char *status = thresholds.getMoistureStatus(moisture);
      int ledPin = thresholds.getLEDPin(moisture);

      display.showStatus(status);
      digitalWrite(ledPin, HIGH);
    }
    else
    {
      display.showValue(uvIndex);

      if (uvIndex < 3)
      {
        display.showStatus("Low UV");
        digitalWrite(12, HIGH);
      }
      else if (uvIndex < 6)
      {
        display.showStatus("Moderate UV");
        digitalWrite(11, HIGH);
      }
      else if (uvIndex < 8)
      {
        display.showStatus("High UV");
        digitalWrite(10, HIGH);
      }
      else if (uvIndex < 11)
      {
        display.showStatus("Very High UV");
        digitalWrite(9, HIGH);
      }
      else
      {
        display.showStatus("Extreme UV");
        digitalWrite(8, HIGH);
      }
    }
  }

  delay(100);
}