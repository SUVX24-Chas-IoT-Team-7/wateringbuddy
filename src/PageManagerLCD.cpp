#include "PageManagerLCD.hpp"

PageManagerLCD::PageManagerLCD(ThresholdManager* manager) 
    : m_manager { manager } {}


    void PageManagerLCD::clearBuffer(char* buffer) {
        memset(buffer, 0, bufferSize);
    }

    void PageManagerLCD::composeLine(char* line, const char* text) {
        // clear line
        clearBuffer(line);
        // add text 
        strncat(line, text, bufferSize - strlen(line) - 1);
    }
    void PageManagerLCD::composeLine(char* line, const char* text, int value, const char* unit) {
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
    }

    void PageManagerLCD::updateCurrentPage(DisplayMode mode, int sensorValue){
        switch (mode)
        {
            // TODO: move operations into helper functions
            case MOISTURE_DISPLAY:
            // line 1
//            clearBuffer(line1);
            composeLine(line1, "Moist: ", sensorValue, "%");
            // line 2
//            clearBuffer(line2);
            composeLine(line2, m_manager->getMoistureString(sensorValue));
            break;
        case LIGHT_DISPLAY:
            break;
        case MOISTURE_TRESHOLD_DISPLAY:
            break;
        case WATERING_DISPLAY:
            break;
        case ADJUST_MOISTURE_DISPLAY:
            break;
        default:
            break;
        }
    }


