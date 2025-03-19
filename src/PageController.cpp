#include "PageController.hpp"


void PageController::processToggleButton(){
    ButtonState currentState = m_buttonToggleMode.getState();
    switch(m_currentMode) {
        
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