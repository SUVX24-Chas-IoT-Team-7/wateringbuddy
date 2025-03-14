#include "../include/LCDDisplay.hpp"
#include "../include/MoistureSensor.hpp"
#include "../include/UVSensor.hpp"
#include "../include/ButtonHandler.hpp"
#include <Arduino.h>

// Create instances of our classes
LCDDisplay display;
MoistureSensor moistureSensor(A0, A1); // Power pin, sensor pin
UVSensor uvSensor(A2);                 // UV sensor pin
ButtonHandler button(2);               // Button pin

// Display mode (0 for moisture, 1 for UV)
int displayMode = 0;

void setup()
{
  // Initialize components
  display.begin();
  moistureSensor.begin();
  uvSensor.begin();
  button.begin();

  // Initialize LED pins
  for (int pin = 8; pin <= 12; pin++)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  pinMode(3, OUTPUT);

  // Initial display setup
  display.showTitle("Soil Moisture");

  Serial.begin(9600);
}

void loop()
{
  // Check for button press to switch modes
  if (button.isPressed())
  {
    displayMode = !displayMode; // Toggle between 0 and 1
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

  // Read sensor values
  int moisture = moistureSensor.readMoisture();
  int uvIndex = uvSensor.readUVIndex();

  // Update analog output (if needed)
  analogWrite(3, moistureSensor.getRawValue());

  // Print to serial monitor
  Serial.print("Moisture = ");
  Serial.print(moisture);
  Serial.print(", UV Index = ");
  Serial.println(uvIndex);

  // Reset all LEDs
  for (int pin = 8; pin <= 12; pin++)
  {
    digitalWrite(pin, LOW);
  }

  // Update display and LEDs based on current mode
  if (displayMode == 0)
  {
    // Moisture display
    display.showValue(moisture);

    // Set status and LEDs based on moisture
    if (moisture < 200)
    {
      display.showStatus("Very Wet");
      digitalWrite(12, HIGH);
    }
    else if (moisture < 400)
    {
      display.showStatus("Wet");
      digitalWrite(11, HIGH);
    }
    else if (moisture < 600)
    {
      display.showStatus("Moist");
      digitalWrite(10, HIGH);
    }
    else if (moisture < 800)
    {
      display.showStatus("Dry");
      digitalWrite(9, HIGH);
    }
    else
    {
      display.showStatus("Very Dry");
      digitalWrite(8, HIGH);
    }
  }
  else
  {
    // UV display
    display.showValue(uvIndex);

    // Set status and LEDs based on UV index
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

  delay(100);
}