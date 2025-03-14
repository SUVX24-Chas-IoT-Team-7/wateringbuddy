#ifndef LCD_DISPLAY_HPP
#define LCD_DISPLAY_HPP

#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

class LCDDisplay
{
private:
    Adafruit_LiquidCrystal lcd;

public:
    LCDDisplay() : lcd(0x20) {} // Initialize with default I2C address

    void begin()
    {
        lcd.begin(16, 2); // 16 columns, 2 rows
        lcd.setBacklight(HIGH);
        lcd.clear();
    }

    void clear()
    {
        lcd.clear();
    }

    void showTitle(const char *title)
    {
        lcd.setCursor(0, 0);
        lcd.print(title);
        lcd.print("      "); // Clear remaining characters
    }

    void showStatus(const char *status)
    {
        lcd.setCursor(0, 0);
        lcd.print(status);
        lcd.print("      "); // Clear remaining characters
    }

    void showValue(int value)
    {
        lcd.setCursor(0, 1);
        lcd.print("Value: ");
        lcd.print(value);
        lcd.print("   "); // Clear remaining characters
    }
};

#endif