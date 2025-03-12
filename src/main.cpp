#include <Arduino.h>

#include "Sensor.hpp"
#include "Pin.hpp"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Pin humidity{ A0, INPUT };

//#define MOISTSENSOR_EXISTS

const int uvReadingPin = A2;
int uvReading = 0;
int prevUvReading = uvReading;
float uvPercent = 0;

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

void setup()
{
  uint8_t value = humidity.read();
  
  //lcd.begin(16, 2);
  //pinMode(switchPin, INPUT);
  // initialize the lcd 
  lcd.init();                      
  lcd.backlight();
  
  // sensors
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);


  // set ledPins to OUTPUT
  for (auto pin : moisture::ledPins) {
    pinMode(pin, OUTPUT);
  }

}

void loop()
  {

    // Simplified potentiometer version
  moisture::rawReading = analogRead(moisture::readingPin);
  moisture::percent = map(moisture::rawReading, 1, 1023, 0, 100);

//   lcd.print("Hello LCD ");
//   lcd.print(test);

  #ifdef MOISTSENSOR_EXISTS
  // Apply power to the soil moisture sensor
  digitalWrite(moisture::powerPin, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moistureReading = analogRead(moisture::readingPin);
  // Turn off the sensor to reduce metal corrosion
  // over time
  digitalWrite(moisture::powerPin, LOW);
  //Serial.println(moisture);
  #endif


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
  

  Serial.print("Moist: ");
  Serial.println(moisture::rawReading);
	//  print sensor values to lcd
//  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moist:     ");
  lcd.setCursor(8, 0);
  lcd.print(moisture::percent);
  lcd.print("%");

  delay(500); // Wait for 500 millisecond(s)
}




