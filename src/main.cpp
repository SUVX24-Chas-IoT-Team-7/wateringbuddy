#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SOIL_SENSOR A0
#define UV_SENSOR A1

#define LED_DRY 6
#define LED_GOOD 7
#define LED_WET 8
#define LED_UV 9

void setup()
{
    Serial.begin(9600);

    lcd.begin(16, 2);
    lcd.backlight();

    pinMode(LED_DRY, OUTPUT);
    pinMode(LED_GOOD, OUTPUT);
    pinMode(LED_WET, OUTPUT);
    pinMode(LED_UV, OUTPUT);
}

void loop()
{
    int soilValue = analogRead(SOIL_SENSOR);
    int uvValue = analogRead(UV_SENSOR);

    Serial.print("Jordfuktighet: ");
    Serial.println(soilValue);
    Serial.print("UV-nivå: ");
    Serial.println(uvValue);

    lcd.clear();
    lcd.setCursor(0, 0);
    if (soilValue < 300)
    {
        digitalWrite(LED_DRY, HIGH);
        digitalWrite(LED_GOOD, LOW);
        digitalWrite(LED_WET, LOW);
        lcd.print("Jorden ar torr!");
    }
    else if (soilValue >= 300 && soilValue < 700)
    {
        digitalWrite(LED_DRY, LOW);
        digitalWrite(LED_GOOD, HIGH);
        digitalWrite(LED_WET, LOW);
        lcd.print("Fuktigheten ar OK");
    }
    else
    {
        digitalWrite(LED_DRY, LOW);
        digitalWrite(LED_GOOD, LOW);
        digitalWrite(LED_WET, HIGH);
        lcd.print("Jorden ar for blot");
    }

    lcd.setCursor(0, 1);
    if (uvValue > 600)
    {
        digitalWrite(LED_UV, HIGH);
        lcd.print("For ljust!");
    }
    else if (uvValue < 200)
    {
        digitalWrite(LED_UV, HIGH);
        lcd.print("For mörkt!");
    }
    else
    {
        digitalWrite(LED_UV, LOW);
        lcd.print("Ljusnivå OK");
    }

    delay(2000);
}
