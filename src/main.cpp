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

//DisplayMode activeMode { UPDATE_DISPLAY };
bool screenHasBeenCleared { false };

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

  // Provide initial sensor values on startup
  moistureSensor.read();
  lightSensor.read();
  uvSensor.read();
}

void loop() {

  // process buttons
  pageController.processToggleButton();
  bool incrementIsPressed = pageController.incrementIsPressed();  
  bool decrementIsPressed = pageController.decrementIsPressed();

  DisplayMode activeMode = pageController.getActiveMode();
  DisplayMode newMode = pageController.getCurrentMode();

  // Set DisplayMode specific timer values
  if (activeMode != newMode && newMode == DisplayMode::WATERING_DISPLAY) {
    pageController.sensorTimer.setDuration(1000);
  }

  if (newMode == DisplayMode::WATERING_DISPLAY) {
    pageController.displayTimer.reset();
  }

  if (activeMode != newMode && newMode == DisplayMode::MOISTURE_DISPLAY) {
    pageController.sensorTimer.setDuration(5 * 60 * 1000);
    pageController.displayTimer.reset();
  }

  // Check if time to clear display
  pageController.checkDisplayTimer();

  // Incr Decr button actions
  if ((newMode == ADJUST_MOISTURE_DISPLAY) && pageController.screenIsActive()) {
    if (incrementIsPressed) {
      moistureStatus.increaseThreshold();
      pageController.setActiveMode(UPDATE_DISPLAY);
    }
    if (decrementIsPressed) {
      moistureStatus.decreaseThreshold();
      pageController.setActiveMode(UPDATE_DISPLAY);
    }
  
  }

  // read new sensor values
  if (pageController.sensorTimer.timeToUpdate()) {
    moistureSensor.read();
    lightSensor.read();
    uvSensor.read();
    pageController.setActiveMode(UPDATE_DISPLAY);
    pageController.sensorTimer.reset();
  }

  // reupdate activeMode
  activeMode = pageController.getActiveMode();
  // Update LCD
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

      pageController.setActiveMode(newMode);
      screenHasBeenCleared = false;
    }

    if (!pageController.screenIsActive() && !screenHasBeenCleared) {
      lcd.clear();
      screenHasBeenCleared = true;
    }


}

