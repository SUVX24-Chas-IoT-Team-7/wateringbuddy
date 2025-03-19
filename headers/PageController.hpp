/**
 * @file PageController.hpp
 * @author Erik Dahl (erik@iunderlandet.se) & John Collinder
 * @brief Class manages buttons and the current state
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __IOT_PAGE_CONTROLLER_CLASS_HPP__
#define __IOT_PAGE_CONTROLLER_CLASS_HPP__

#include "Buttons.hpp"
#include "ThresholdManager.hpp"

class PageController {
private:
    Button m_buttonToggleMode;
    Button m_buttonDecrement;    
    Button m_buttonIncrement;
    DisplayMode m_currentMode;
public:
    PageController(int togglePin, int decrementPin, int incrementPin);
    void init();
    void processToggleButton();
    bool decrementIsPressed();
    bool incrementIsPressed();
    DisplayMode getCurrentMode();
};




#endif