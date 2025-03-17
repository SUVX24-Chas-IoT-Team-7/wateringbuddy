//#include <Arduino.h>

#include "Sensor.hpp"
#include "Pin.hpp"
#include "Buttons.hpp"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


#define MOISTSENSOR_EXISTS

  enum thresholdNames {
  	DRY,
    GOOD,
    WET
  };

namespace moisture {
  // sensor pins
  const int powerPin = A0;
  const int readingPin = A1;
  // LED pins
  const int redPin = 6;
  const int yellowPin = 7;
  const int greenPin = 8;
  const int bluePin = 9;
  const int ledPins[] = { redPin, yellowPin, greenPin, bluePin };

  int thresholds[] = {25, 50, 70 };

  int rawReading = 0;
  int percent = 0;

} // moisture

namespace uvsensor {
  const int readingPin = A2;
  int rawReading = 0;
  int prevRawReading = rawReading;
  float percent = 0;
  int thresholds[] = {120, 1000};
} // uvsensor

void printToLcdBasic(LiquidCrystal_I2C& lcd);

void setup()
{
  
  // initialize the lcd 
  lcd.init();
  lcd.backlight();
  
  // initialize buttons
  button1.init();

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

  #ifdef MOISTSENSOR_EXISTS
  // Apply power to the soil moisture sensor
  digitalWrite(moisture::powerPin, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moisture::rawReading = analogRead(moisture::readingPin);
  // Turn off the sensor to reduce metal corrosion
  // over time
  digitalWrite(moisture::powerPin, LOW);
  //Serial.println(moisture);
  #else
  // Simplified potentiometer version
  moisture::rawReading = analogRead(moisture::readingPin);  
  #endif
  
  //calculate percent from raw value
  moisture::percent = map(moisture::rawReading, 1, 1023, 100, 0);

  uvsensor::rawReading = analogRead(uvsensor::readingPin);

  // update moisture LEDs
  for (auto pin : moisture::ledPins) {
    digitalWrite(pin, LOW);
  }

  if (moisture::percent < moisture::thresholds[DRY]) {
    digitalWrite(moisture::redPin, HIGH);
  } else if (moisture::percent < moisture::thresholds[GOOD]) {
    digitalWrite(moisture::yellowPin, HIGH);
  } else if (moisture::percent < moisture::thresholds[WET]) {
    digitalWrite(moisture::greenPin, HIGH);
  } else {
    digitalWrite(moisture::bluePin, HIGH);
  }

  // print to serial monitor
  //Serial.print("UV: ");
  //Serial.println(moisture::rawReading);

  printToLcdBasic(lcd);
  


}

void printToLcdBasic(LiquidCrystal_I2C& lcd){
  lcd.setCursor(0, 0);
  lcd.print("Moist:     ");
  lcd.setCursor(7, 0);
  lcd.print(moisture::percent);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Light:     ");
  lcd.setCursor(7, 1);
  lcd.print(uvsensor::rawReading);
}


