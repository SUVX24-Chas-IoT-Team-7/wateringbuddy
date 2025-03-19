/**
 * @file buttonHandler.hpp
 * @author Erik Dahl (erik@iunderlandet.se)
 * @brief Class manages buttons and the current state
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __IOT_BUTTON_HANDLER_CLASS_HPP__
#define __IOT_BUTTON_HANDLER_CLASS_HPP__

#include "Buttons.hpp"
#include "ThresholdManager.hpp"

class ButtonHandler {
private:
    Button m_buttonToggleMode;
    Button m_buttonDecrement;    
    Button m_buttonIncrement;
    DisplayMode m_currentMode;
    void processButtonToggle();
    bool processButtonDecrement();
    bool processButtonIncrement();
public:
    ButtonHandler(int togglePin, int decrementPin, int incrementPin);
    void updateStates();
    DisplayMode getCurrentMode();
};




#endif