#include "TextManager.hpp"

TextManager::TextManager(ThresholdManager* manager) 
    : m_manager { manager } {}


    void TextManager::clearBuffer(char* buffer) {
        memset(buffer, 0, bufferSize);
    }

    void TextManager::composeLine(char* line, const char* text) {
        // clear line
        clearBuffer(line);
        // add text 
        strncat(line, text, bufferSize - strlen(line) - 1);
    }
    void TextManager::composeLine(char* line, const char* text, int value, const char* unit, const char* info) {
        // clear line
        clearBuffer(line);
        // add text 
        strncat (line, text, bufferSize - strlen(line) - 1);
        // add current sensorValue
        char valueStr[bufferSize];
        snprintf(valueStr,sizeof(valueStr), "%d", value);
        strncat(line, valueStr, bufferSize - strlen(line) - 1);
        // add unit
        strncat(line, unit, bufferSize - strlen(line) - 1);
        if (info != nullptr) {
            strncat(line, info, bufferSize - strlen(line) - 1);
        }
    }

    const char* TextManager::getLine1(){
        return line1;
    }

    const char* TextManager::getLine2(){
        return line2;
    }

    void TextManager::updateCurrentPage(DisplayMode mode, int sensorValue, int sensorValue2){
        switch (mode)
        {
            case MOISTURE_DISPLAY:
            composeLine(line1, "Moist: ", sensorValue, "%");
            composeLine(line2, m_manager->getMoistureString(sensorValue));
            break;
            
            case LIGHT_DISPLAY:
            composeLine(line1, "Light: ", sensorValue);
            composeLine(line2, "UV: ", sensorValue2);
            break;
            
            case MOISTURE_TRESHOLD_DISPLAY:
            composeLine(line1, "Moisture Center");
            composeLine(line2, "Value: ", m_manager->getMoistureCenterValue(), "%");
            break;
            
            case WATERING_DISPLAY:
            composeLine(line1, "Watering Mode");
            composeLine(line2, "Moist: ", sensorValue, "% ", m_manager->getMoistureShortString(sensorValue));
            break;
        
            case LIGHT_FASTMODE_DISPLAY:
            composeLine(line1, "Light: ", sensorValue, " Fast");
            composeLine(line2, "UV: ", sensorValue2, "    Mode");
            break;

            case ADJUST_MOISTURE_DISPLAY:
            composeLine(line1, "Set Center Value");
            composeLine(line2, "       ", m_manager->getMoistureCenterValue(), "%");
            break;
        
            default:
            break;
        }
    }


