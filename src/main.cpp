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

  // process buttons
  pageController.processToggleButton();
  bool incrementIsPressed = pageController.incrementIsPressed();  
  bool decrementIsPressed = pageController.decrementIsPressed();

  DisplayMode newMode = pageController.getCurrentMode();

  if (activeMode != newMode && newMode == DisplayMode::WATERING_DISPLAY) {
    pageController.sensorTimer.setDuration(1000);
  }

  if (newMode == DisplayMode::WATERING_DISPLAY) {
    pageController.displayTimer.reset();
  }

  if (activeMode != newMode && newMode == DisplayMode::MOISTURE_DISPLAY) {
    pageController.sensorTimer.setDuration();
    pageController.displayTimer.reset();
  }

  // Removed Clear Screen for debugging purposes
  // pageController.checkDisplayTimer();


  if ((newMode == ADJUST_MOISTURE_DISPLAY) && pageController.screenIsActive()) {
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

    if (pageController.screenIsActive() && activeMode != newMode) {

      switch(newMode) {
        case MOISTURE_DISPLAY:
        case WATERING_DISPLAY:
        textManager.updateCurrentPage(newMode, moistureSensor.getPercentage());
        break;
        case LIGHT_DISPLAY:
        textManager.updateCurrentPage(newMode, lightSensor.getData(), uvSensor.getData());
        break;
        case MOISTURE_TRESHOLD_DISPLAY:
        case ADJUST_MOISTURE_DISPLAY:
        textManager.updateCurrentPage(newMode);
        break;
        default:   
        ;     
        }
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(textManager.getLine1());
      lcd.setCursor(0,1);
      lcd.print(textManager.getLine2());
      
      Serial.println(textManager.getLine1());
      Serial.println(textManager.getLine2());

      activeMode = newMode;
    }

    // TODO: Just do this once. How to fix?
    if (!pageController.screenIsActive()) {
      lcd.clear();
    }


}

