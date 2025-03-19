#include "PageController.hpp"

void PageController::processToggleButton(){

    ButtonState currentState = m_buttonToggleMode.getState();
    // Active mode reset implementation goes here

    switch(m_currentMode) {
        case MOISTURE_DISPLAY:
        if (currentState == SHORTPRESS) {
            m_currentMode = LIGHT_DISPLAY;  // go to page 1
        }
        else if (currentState == LONGPRESS) {
            m_currentMode = WATERING_DISPLAY;
        }
        break;

        case LIGHT_DISPLAY:
        if (currentState == SHORTPRESS) {
            m_currentMode = MOISTURE_TRESHOLD_DISPLAY;  // go to page 2
        }
        else if (currentState == LONGPRESS) {
            // No implementation yet
        }
        break;

        case MOISTURE_TRESHOLD_DISPLAY:
        if (currentState == SHORTPRESS) {
            m_currentMode = MOISTURE_DISPLAY;           // go to page 0
        }
        else if (currentState == LONGPRESS) {
            m_currentMode = ADJUST_MOISTURE_DISPLAY;
        }
        break;

        case WATERING_DISPLAY:
        if (currentState == SHORTPRESS) {
            m_currentMode = MOISTURE_DISPLAY;
        }
        break;

        case ADJUST_MOISTURE_DISPLAY:
        if (currentState == SHORTPRESS) {
            m_currentMode = MOISTURE_TRESHOLD_DISPLAY;
        }

        break;

    }    
}
bool PageController::decrementIsPressed(){
    return (m_buttonDecrement.getState() == SHORTPRESS);
}
bool PageController::incrementIsPressed(){
    return (m_buttonIncrement.getState() == SHORTPRESS);
}

PageController::PageController(int togglePin, int decrementPin, int incrementPin)
    : m_buttonToggleMode { togglePin, INPUT }, 
      m_buttonDecrement { decrementPin, INPUT },
      m_buttonIncrement { incrementPin, INPUT },
      m_currentMode { MOISTURE_DISPLAY }  {}

DisplayMode PageController::getCurrentMode(){
    return m_currentMode;
}