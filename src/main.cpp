//#include <Arduino.h>

#include "Sensor.hpp"
#include "Pin.hpp"
#include "Buttons.hpp"
//#include "ThresholdManager.hpp"
#include "PageManagerLCD.hpp"
#include "MoistureSensor.hpp"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

ThresholdManager moistureStatus;
PageManagerLCD pageManager(&moistureStatus);

MoistureSensor moistureSensor{ A0, A1, MoistureSensor::LedPins{moisture::greenPin, moisture::yellowPin, moisture::redPin, moisture::bluePin}, &moistureStatus };

void printToLcdBasic(LiquidCrystal_I2C& lcd);

void setup()
{
  
  // initialize the lcd 
  lcd.init();
  lcd.backlight();
  
  // TODO: initialize buttons
  
  // initialize sensors
  moistureSensor.init();

  // enable Serial monitoring
  Serial.begin(9600);



}

void loop() {

  // read new sensor values


  // Apply power to the soil moisture sensor
  moistureSensor.read();

  pageManager.updateCurrentPage(DisplayMode::MOISTURE_DISPLAY, moistureSensor.getPercentage());
  //pageManager.updateCurrentPage(DisplayMode::LIGHT_DISPLAY, uvsensor::rawReading, 200);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(pageManager.getLine1());
  lcd.setCursor(0,1);
  lcd.print(pageManager.getLine2());

  Serial.println(pageManager.getLine1());
  Serial.println(pageManager.getLine2());

  // printToLcdBasic(lcd);
  delay(500);

}

