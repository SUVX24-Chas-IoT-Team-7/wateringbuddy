#include "PageManagerLCD.hpp"

PageManagerLCD::PageManagerLCD(ThresholdManager* manager) 
    : m_manager { manager } {}


    void PageManagerLCD::updateCurrentPages(DisplayMode mode, int sensorValue){
        switch (mode)
        {
            // TODO: move operations into helper functions
            case MOISTURE_DISPLAY:
            // page 1
            // clear page1 variable
            memset(page1, 0, 17);
            // add Moist: 
            strncat (page1, "Moist: ", sizeof(page1) - strlen(page1) - 1);
            // add current sensorValue
            char moistStr[16];
            snprintf(moistStr,sizeof(moistStr), "%d", sensorValue);
            strncat(page1, moistStr, sizeof(page1) - strlen(page1) - 1);
            // add %
            strncat(page1, "%", sizeof(page1) - strlen(page1) - 1);
            // page 2
            memset(page2, 0, 16);
            // add message from m_manager
            strncat(page2, m_manager->getMoistureString(sensorValue), sizeof(page2) - strlen(page2) - 1);
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


