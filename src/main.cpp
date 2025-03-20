//#include <Arduino.h>

#include "Sensor.hpp"
#include "Pin.hpp"
#include "Buttons.hpp"
#include "MoistureSensor.hpp"
#include "TextManager.hpp"
#include "PageController.hpp"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

ThresholdManager moistureStatus;
TextManager textManager(&moistureStatus);
PageController pageController(pushButtons::TglPin, pushButtons::DecrPin, pushButtons::IncrPin);

MoistureSensor moistureSensor{ moisture::powerPin, moisture::readingPin, MoistureSensor::LedPins{moisture::greenPin, moisture::yellowPin, moisture::redPin, moisture::bluePin}, &moistureStatus };
Sensor lightSensor { lightSensors::lightReadingPin, INPUT };
Sensor uvSensor { lightSensors::uvReadingPin, INPUT };

DisplayMode activeMode { UPDATE_DISPLAY };

void setup()
{
  
  // initialize the lcd 
  lcd.init();
  lcd.backlight();
  
  // initialize the pageController buttons
  pageController.init();

  // initialize sensors
  moistureSensor.init();
  lightSensor.init();
  uvSensor.init();

  // enable Serial monitoring
  Serial.begin(9600);



}

void loop() {


  pageController.processToggleButton();

  bool incrementIsPressed = pageController.incrementIsPressed();  
  bool decrementIsPressed = pageController.decrementIsPressed();

  // TODO: When DisplayMode == WATERING_DISPLAY, either reset timer or don't call checkDisplayTimer
  // Removed Clear Screen for debugging purposes
  // pageController.checkDisplayTimer();


  if ((pageController.getCurrentMode() == ADJUST_MOISTURE_DISPLAY) && pageController.screenIsActive()) {
    if (incrementIsPressed) Serial.println("Increment is pressed");
    if (decrementIsPressed) Serial.println("Decrement is pressed");

    if (incrementIsPressed) {
      moistureStatus.increaseThreshold();
      activeMode = UPDATE_DISPLAY;
    }
    if (decrementIsPressed) {
      moistureStatus.decreaseThreshold();
      activeMode = UPDATE_DISPLAY;
    }
  
  }

  // read new sensor values
  if (pageController.sensorTimer.timeToUpdate()) {
    moistureSensor.read();
    lightSensor.read();
    uvSensor.read();
    activeMode = UPDATE_DISPLAY;
    pageController.sensorTimer.reset();
  }

    if (pageController.screenIsActive() && activeMode != pageController.getCurrentMode()) {

      textManager.updateCurrentPage(pageController.getCurrentMode(), moistureSensor.getPercentage());
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(textManager.getLine1());
      lcd.setCursor(0,1);
      lcd.print(textManager.getLine2());
      
      Serial.println(textManager.getLine1());
      Serial.println(textManager.getLine2());

      activeMode = pageController.getCurrentMode();
    }
    // TODO: Just do this once. How to fix?
    if (!pageController.screenIsActive()) {
      lcd.clear();
    }


}

