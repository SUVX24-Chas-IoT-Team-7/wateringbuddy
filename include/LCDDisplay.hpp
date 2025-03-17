
#ifndef LCD_DISPLAY_HPP
#define LCD_DISPLAY_HPP
/**
 * @file LCDDisplay.hpp
 * @author John Collinder
 * @brief   LCDDisplay class to handle LCD display
 *        This class is used to handle the LCD display. It shows the title, status and value on the display
 *      It also clears the display
 * @version 0.1
 * @date 2025-03-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

class LCDDisplay
{
private:
    Adafruit_LiquidCrystal lcd;

public:
    LCDDisplay() : lcd(0x20) {}

    void begin()
    {
        lcd.begin(16, 2);
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
        lcd.print("      ");
    }

    void showStatus(const char *status)
    {
        lcd.setCursor(0, 0);
        lcd.print(status);
        lcd.print("      ");
    }

    void showValue(int value)
    {
        lcd.setCursor(0, 1);
        lcd.print("Value: ");
        lcd.print(value);
        lcd.print("   ");
    }
};

#endif