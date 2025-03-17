#ifndef PAGE_MANAGER_LCD_HPP
#define PAGE_MANAGER_LCD_HPP

#include <PageManagerLCD.hpp>
#include <ConstantsAndEnums.hpp>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

class PageManagerLCD
{
private:
    LiquidCrystal_I2C m_lcd;

    void printToLcdBasic()
    {
        lcd.setCursor(0, 0);
        lcd.print("Moist:     ");
        lcd.setCursor(7, 0);
        lcd.print(moisture::percent);
        lcd.print("%");
        lcd.setCursor(0, 1);
        lcd.print(moistureStatus.getMoistureString(moisture::percent));
    }

public:
    PageManagerLCD() : m_lcd{0x27, 16, 2} {};

    void updateLCD(displayMode mode)
    {
        switch (mode)
        {
        case displayMode::MOISTURE_DISPLAY:
            printToLcdBasic();
            break;
        case displayMode::LIGHT_DISPLAY:
            break;
        case displayMode::MOISTURE_TRESHOLD_DISPLAY:
            break;
        case displayMode::WATERING_DISPLAY:
            break;
        case displayMode::ADJUST_MOISTURE_DISPLAY:
            break;
        default:
            break;
        }
    }
};

PageManagerLCD::PageManagerLCD()
{
}

#endif