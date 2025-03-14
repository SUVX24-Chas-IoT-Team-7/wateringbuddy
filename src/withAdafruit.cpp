#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd(0x20);

int sensorValue = 0;
int outputValue = 0;
int moisture = 0;

void setup()
{

    lcd.begin(16, 2);
    lcd.setBacklight(HIGH);
    lcd.clear();
    lcd.print("Soil Moisture");

    pinMode(A0, OUTPUT);
    pinMode(A1, INPUT);
    Serial.begin(9600);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(3, OUTPUT);
}

void loop()
{

    sensorValue = analogRead(A1);

    analogWrite(3, sensorValue);

    Serial.print("sensor = ");
    Serial.println(sensorValue);

    digitalWrite(A0, HIGH);
    delay(10);
    moisture = analogRead(A1);

    digitalWrite(A0, LOW);
    Serial.println(moisture);

    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.print(moisture);
    lcd.print("   ");

    lcd.setCursor(0, 0);
    if (moisture < 200)
    {
        lcd.print("Very Dry      ");
        digitalWrite(12, HIGH);
    }
    else if (moisture < 400)
    {
        lcd.print("Dry           ");
        digitalWrite(11, HIGH);
    }
    else if (moisture < 600)
    {
        lcd.print("Moist         ");
        digitalWrite(10, HIGH);
    }
    else if (moisture < 800)
    {
        lcd.print("Wet           ");
        digitalWrite(9, HIGH);
    }
    else
    {
        lcd.print("Very Wet      ");
        digitalWrite(8, HIGH);
    }

    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);

    if (moisture < 200)
    {
        digitalWrite(12, HIGH);
    }
    else if (moisture < 400)
    {
        digitalWrite(11, HIGH);
    }
    else if (moisture < 600)
    {
        digitalWrite(10, HIGH);
    }
    else if (moisture < 800)
    {
        digitalWrite(9, HIGH);
    }
    else
    {
        digitalWrite(8, HIGH);
    }

    delay(100);
}