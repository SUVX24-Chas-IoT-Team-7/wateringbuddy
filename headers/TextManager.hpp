#ifndef PAGE_MANAGER_LCD_HPP
#define PAGE_MANAGER_LCD_HPP

#include "ThresholdManager.hpp"
#include "ConstantsAndEnums.hpp"
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>


class TextManager
{
private:
    ThresholdManager* m_manager;
    static const int bufferSize { 16 + 1 };
    char line1[bufferSize];
    char line2[bufferSize];
    void clearBuffer(char* buffer);
    void composeLine(char* line, const char* text);
    void composeLine(char* line, const char* text, int value, const char* unit = "");

public:
    TextManager(ThresholdManager* manager);
    const char* getLine1();
    const char* getLine2();
    void updateCurrentPage(DisplayMode mode, int sensorValue = 0, int sensorValue2 = 0);
};

#endif