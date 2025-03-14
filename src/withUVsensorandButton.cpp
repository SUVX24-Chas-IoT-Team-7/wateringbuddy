#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0x20);

const int BUTTON_PIN = 2;
const int UV_SENSOR_PIN = A2;
const int MOISTURE_POWER_PIN = A0;
const int MOISTURE_SENSOR_PIN = A1;

int sensorValue = 0;
int outputValue = 0;
int moisture = 0;
int uvIndex = 0;
int displayMode = 0;
bool buttonPressed = false;

void setup()
{
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.print("Soil Moisture");

  pinMode(MOISTURE_POWER_PIN, OUTPUT);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  pinMode(UV_SENSOR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed)
  {
    buttonPressed = true;
    displayMode = !displayMode;
    lcd.clear();

    if (displayMode == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("Soil Moisture");
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("UV Index");
    }
    delay(200);
  }
  else if (digitalRead(BUTTON_PIN) == HIGH)
  {
    buttonPressed = false;
  }

  sensorValue = analogRead(MOISTURE_SENSOR_PIN);
  analogWrite(3, sensorValue);

  digitalWrite(MOISTURE_POWER_PIN, HIGH);
  delay(10);
  moisture = analogRead(MOISTURE_SENSOR_PIN);
  digitalWrite(MOISTURE_POWER_PIN, LOW);

  int uvValue = analogRead(UV_SENSOR_PIN);
  float uvVoltage = uvValue * (5.0 / 1023.0);
  uvIndex = round(uvVoltage * 10);

  Serial.print("Moisture = ");
  Serial.print(moisture);
  Serial.print(", UV Index = ");
  Serial.println(uvIndex);

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  if (displayMode == 0)
  {
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.print(moisture);
    lcd.print("   ");

    if (moisture < 200)
    {
      lcd.setCursor(0, 0);
      lcd.print("Very Wet      ");
      digitalWrite(12, HIGH);
    }
    else if (moisture < 400)
    {
      lcd.setCursor(0, 0);
      lcd.print("Wet           ");
      digitalWrite(11, HIGH);
    }
    else if (moisture < 600)
    {
      lcd.setCursor(0, 0);
      lcd.print("Moist         ");
      digitalWrite(10, HIGH);
    }
    else if (moisture < 800)
    {
      lcd.setCursor(0, 0);
      lcd.print("Dry           ");
      digitalWrite(9, HIGH);
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("Very Dry      ");
      digitalWrite(8, HIGH);
    }
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.print(uvIndex);
    lcd.print("   ");

    lcd.setCursor(0, 0);
    if (uvIndex < 3)
    {
      lcd.print("Low UV        ");
      digitalWrite(12, HIGH);
    }
    else if (uvIndex < 6)
    {
      lcd.print("Moderate UV   ");
      digitalWrite(11, HIGH);
    }
    else if (uvIndex < 8)
    {
      lcd.print("High UV       ");
      digitalWrite(10, HIGH);
    }
    else if (uvIndex < 11)
    {
      lcd.print("Very High UV  ");
      digitalWrite(9, HIGH);
    }
    else
    {
      lcd.print("Extreme UV    ");
      digitalWrite(8, HIGH);
    }
  }

  delay(100);
}