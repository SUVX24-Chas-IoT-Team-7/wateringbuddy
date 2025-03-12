#include <Arduino.h>
#include "Pin.hpp"

Pin humidity{ A0, INPUT };

#include <LiquidCrystal.h>
//#define MOISTSENSOR_EXISTS

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int test = 0;

const int switchPin = 6;

const int moistPowerPin = A0;
const int moistReadingPin = A1;
const int uvReadingPin = A2;


int moistureReading = 0;
int moisturePercent = 0;
int uvReading = 0;
int prevUvReading = uvReading;
float uvPercent = 0;

  enum thresholdNames {
	DRY,
    GOOD,
    WET
  };

namespace moisture {
    
  int thresholds[] = {25, 50, 70 };

  const int redPin = 6;
  const int yellowPin = 7;
  const int greenPin = 8;
  const int bluePin = 9;
  const int ledPins[] = { redPin, yellowPin, greenPin, bluePin };
  
} // moisture

void setup()
{
  uint8_t value = humidity.read();
  
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
    
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
  moistureReading = analogRead(moistReadingPin);
  moisturePercent = map(moistureReading, 1, 1023, 0, 100);

//   lcd.print("Hello LCD ");
//   lcd.print(test);

  #ifdef MOISTSENSOR_EXISTS
  // Apply power to the soil moisture sensor
  digitalWrite(moistPowerPin, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moistureReading = analogRead(moistReadingPin);
  // Turn off the sensor to reduce metal corrosion
  // over time
  digitalWrite(moistPowerPin, LOW);
  //Serial.println(moisture);
  #endif


  for (auto pin : moisture::ledPins) {
    digitalWrite(pin, LOW);
  }
  
  if (moisturePercent < moisture::thresholds[DRY]) {
    digitalWrite(moisture::redPin, HIGH);
  } else if (moisturePercent < moisture::thresholds[GOOD]) {
    digitalWrite(moisture::yellowPin, HIGH);
  } else if (moisturePercent < moisture::thresholds[WET]) {
    digitalWrite(moisture::greenPin, HIGH);
  } else {
    digitalWrite(moisture::bluePin, HIGH);
  }
  

  Serial.print("Moist: ");
  Serial.println(moistureReading);
	//  print sensor values to lcd
//  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moist:     ");
  lcd.setCursor(8, 0);
  lcd.print(moisturePercent);
  lcd.print("%");

  delay(500); // Wait for 500 millisecond(s)
}




