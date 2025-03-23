/**
 * @file PageController.hpp
 * @author Erik Dahl (erik@iunderlandet.se) & John Collinder
 * @brief This class manages buttons and the current state of displaymode and LCD
 * @version 0.1
 * @date 2025-03-18
 */
#ifndef __IOT_PAGE_CONTROLLER_CLASS_HPP__
#define __IOT_PAGE_CONTROLLER_CLASS_HPP__

#include "Buttons.hpp"
#include "ThresholdManager.hpp"
#include "Timer.hpp"

/**
 * @brief This class manages buttons and the current state of displaymode and LCD
 * 
 */
class PageController
{
private:
    /**
     * @brief  Button to toggle between modes
     */
    Button m_buttonToggleMode;
    Button m_buttonDecrement;
    Button m_buttonIncrement;
    DisplayMode m_currentMode;
    /**
     * @brief Set to UPDATE_DISPLAY so screen will update on startup
     */
    DisplayMode m_activeMode { UPDATE_DISPLAY };
  
    bool m_screenIsActive{ true };
  
public:
    /**
     * @brief Construct a new Page Controller object
     * @param togglePin
     * @param decrementPin
     * @param incrementPin
     */
    PageController(int togglePin, int decrementPin, int incrementPin);
  
    Timer displayTimer { 30 * 1000 };
    Timer sensorTimer { 5 * 60 * 1000 };

    /**
     * @brief  Initialize the buttons
     */
    void init();
    /**
     * @brief  Process the button presses
     */
    void processToggleButton();
    /**
     * @brief  Process the decrement button
     * @return true
     * @return false
     */
    bool decrementIsPressed();
    /**
     * @brief  Process the increment button
     * @return true
     * @return false
     */
    bool incrementIsPressed();

    /**
     * @brief  Get the Current Mode object, i.e. the new mode
     * @return DisplayMode
     */
    DisplayMode getCurrentMode();
    /**
     * @brief Get the Active Mode object, i.e. the old mode
     * 
     * @return DisplayMode 
     */
    DisplayMode getActiveMode();
    /**
     * @brief Set the Active Mode object
     * 
     * @param mode 
     */
    void setActiveMode(DisplayMode mode);

    bool screenIsActive();
    void checkDisplayTimer();
};

#endif