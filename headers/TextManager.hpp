#ifndef PAGE_MANAGER_LCD_HPP
#define PAGE_MANAGER_LCD_HPP
/**
 * @file TextManager.hpp
 * @author your name (you@domain.com)
 * @brief  TextManager class to handle text on the LCD
 * @details This class is used to handle text on the LCD
 * It has methods to update the text on the LCD
 * @version 0.1
 * @date 2025-03-20
 */
#include "ThresholdManager.hpp"
#include "ConstantsAndEnums.hpp"
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>

class TextManager
{
private:
    ThresholdManager *m_manager;
    static const int bufferSize{16 + 1};
    char line1[bufferSize];
    char line2[bufferSize];
    /**
     * @brief  Clear the buffer
     * @param buffer
     */
    void clearBuffer(char *buffer);
    /**
     * @brief  Compose a line of text
     * @param line
     * @param text
     */
    void composeLine(char *line, const char *text);
    /**
     * @brief  Compose a line of text with a value
     * @param line
     * @param text
     * @param value
     * @param unit
     */
    void composeLine(char *line, const char *text, int value, const char *unit = "", const char* info = nullptr);

public:
    /**
     * @brief Construct a new Text Manager object
     * @param manager
     */
    TextManager(ThresholdManager* manager);
    const char* getLine1();
    const char* getLine2();
     /**
     * @brief  Update the text that gets printed on the LCD
     * @param mode
     * @param sensorValue defaults to 0 for modes that does not use it
     * @param sensorValue2 defaults to 0 for modes that does not use it
     */  
     void updateCurrentPage(DisplayMode mode, int sensorValue = 0, int sensorValue2 = 0);
};

#endif