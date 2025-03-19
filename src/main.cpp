//#include <Arduino.h>

#include "Sensor.hpp"
#include "Pin.hpp"
#include "Buttons.hpp"
//#include "ThresholdManager.hpp"
#include "MoistureSensor.hpp"
#include "TextManager.hpp"
#include "PageController.hpp"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

ThresholdManager moistureStatus;
TextManager textManager(&moistureStatus);
PageController pageController(pushButtons::TglPin, pushButtons::DecrPin, pushButtons::IncrPin);

MoistureSensor moistureSensor{ A0, A1, MoistureSensor::LedPins{moisture::greenPin, moisture::yellowPin, moisture::redPin, moisture::bluePin}, &moistureStatus };

DisplayMode activeMode { UPDATE_DISPLAY };

void printToLcdBasic(LiquidCrystal_I2C& lcd);

void setup()
{
  
  // initialize the lcd 
  lcd.init();
  lcd.backlight();
  
  // TODO: initialize buttons
  pageController.init();

  // initialize sensors
  moistureSensor.init();

  // enable Serial monitoring
  Serial.begin(9600);



}

void loop() {


  pageController.processToggleButton();

  // read new sensor values
  if (pageController.sensorTimer.timeToUpdate()) {
    moistureSensor.read();
    activeMode = UPDATE_DISPLAY;
    pageController.sensorTimer.reset();
  }

    if (pageController.screenIsActive() && activeMode != pageController.getCurrentMode()) {

      textManager.updateCurrentPage(pageController.getCurrentMode(), moistureSensor.getPercentage());
      //textManager.updateCurrentPage(DisplayMode::LIGHT_DISPLAY, uvsensor::rawReading, 200);
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(textManager.getLine1());
      lcd.setCursor(0,1);
      lcd.print(textManager.getLine2());
      
      Serial.println(textManager.getLine1());
      Serial.println(textManager.getLine2());

      activeMode = pageController.getCurrentMode();
    }

  // printToLcdBasic(lcd);
  // delay(500);

}

