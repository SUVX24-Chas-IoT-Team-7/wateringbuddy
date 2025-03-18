//#include <Arduino.h>

#include "Sensor.hpp"
#include "Pin.hpp"
#include "Buttons.hpp"
//#include "ThresholdManager.hpp"
#include "PageManagerLCD.hpp"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


namespace moisture
{
  int thresholds[] = {25, 50, 70};

  int lastReading = 0;
  int rawReading = 0;
  int percent = 0;

} // moisture

namespace uvsensor
{
  int rawReading = 0;
  int prevRawReading = rawReading;
  float percent = 0;
  int thresholds[] = {120, 1000};
} // uvsensor

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display



ThresholdManager moistureStatus;
PageManagerLCD pageManager(&moistureStatus);

void printToLcdBasic(LiquidCrystal_I2C& lcd);

void setup()
{
  
  // initialize the lcd 
  lcd.init();
  lcd.backlight();
  
  // initialize buttons

  
  // initialize sensors
  pinMode(moisture::powerPin, OUTPUT);
  pinMode(moisture::readingPin, INPUT);
  pinMode(uvsensor::readingPin, INPUT);

  // set ledPins to OUTPUT
  for (auto pin : moisture::ledPins) {
    pinMode(pin, OUTPUT);
  }

  // enable Serial monitoring
  Serial.begin(9600);



}

void loop() {

  // read new sensor values


  // Apply power to the soil moisture sensor
  digitalWrite(moisture::powerPin, HIGH);
  delay(10); // Wait for 10 millisecond(s)

  moisture::lastReading = moisture::rawReading;
  moisture::rawReading = analogRead(moisture::readingPin);

  // Turn off the sensor to reduce metal corrosion
  // over time
  digitalWrite(moisture::powerPin, LOW);

  
  //calculate percent from raw value
  moisture::percent = map(moisture::rawReading, 1, 1023, 100, 0);

  uvsensor::rawReading = analogRead(uvsensor::readingPin);

  // update moisture LEDs
  for (auto pin : moisture::ledPins) {
    digitalWrite(pin, LOW);
  }
  int moistPin = moistureStatus.getLEDPin(moisture::percent);
    digitalWrite(moistPin, HIGH);

    pageManager.updateCurrentPages(DisplayMode::MOISTURE_DISPLAY, moisture::percent);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(pageManager.page1);
    lcd.setCursor(0,1);
    lcd.print(pageManager.page2);

    Serial.println(moisture::percent);

  // printToLcdBasic(lcd);
  delay(500);

}

void printToLcdBasic(LiquidCrystal_I2C& lcd){
  lcd.setCursor(0, 0);
  lcd.print("Moist: ");
  lcd.setCursor(7, 0);
  lcd.print(moisture::percent);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print(moistureStatus.getMoistureString(moisture::percent));
}


