#ifndef PAGE_MANAGER_LCD_HPP
#define PAGE_MANAGER_LCD_HPP

#include "ThresholdManager.hpp"
#include "ConstantsAndEnums.hpp"
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>


class PageManagerLCD
{
private:
    ThresholdManager* m_manager;

public:
    PageManagerLCD(ThresholdManager* manager);
    char page1[17];
    char page2[17];
    void updateCurrentPages(DisplayMode mode, int sensorValue);
};

#endif