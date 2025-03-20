#include "PageController.hpp"

PageController::PageController(int togglePin, int decrementPin, int incrementPin)
    : m_buttonToggleMode { togglePin, INPUT }, 
      m_buttonDecrement { decrementPin, INPUT },
      m_buttonIncrement { incrementPin, INPUT },
      m_currentMode { MOISTURE_DISPLAY }  {}

void PageController::init() {
    m_buttonToggleMode.init();
    m_buttonDecrement.init();
    m_buttonIncrement.init();
}

void PageController::processToggleButton(){

    ButtonState currentState = m_buttonToggleMode.getState();
    // on sleep
    if (!m_screenIsActive && currentState) {
        m_screenIsActive = true;
        m_activeMode = UPDATE_DISPLAY;
        displayTimer.reset();
    } else {
        if (currentState) displayTimer.reset();
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
}
bool PageController::decrementIsPressed(){
    return (m_buttonDecrement.getState() == SHORTPRESS);
}
bool PageController::incrementIsPressed(){
    return (m_buttonIncrement.getState() == SHORTPRESS);
}

DisplayMode PageController::getCurrentMode(){
    return m_currentMode;
}

DisplayMode PageController::getActiveMode(){
    return m_activeMode;
}

void PageController::setActiveMode(DisplayMode mode) {
    m_activeMode = mode;
}

bool PageController::screenIsActive(){
    return m_screenIsActive;
}

void PageController::checkDisplayTimer() {
    if (displayTimer.timeToUpdate()) {
        m_screenIsActive = false;
    }
}