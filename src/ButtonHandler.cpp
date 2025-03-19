#include "ButtonHandler.hpp"


void ButtonHandler::processToggleButton(){

}
bool ButtonHandler::decrementIsPressed(){
    return (m_buttonDecrement.getState() == SHORTPRESS);
}
bool ButtonHandler::incrementIsPressed(){
    return (m_buttonIncrement.getState() == SHORTPRESS);
}

ButtonHandler::ButtonHandler(int togglePin, int decrementPin, int incrementPin)
    : m_buttonToggleMode { togglePin, INPUT }, 
      m_buttonDecrement { decrementPin, INPUT },
      m_buttonIncrement { incrementPin, INPUT },
      m_currentMode { MOISTURE_DISPLAY }  {}

DisplayMode ButtonHandler::getCurrentMode(){
    return m_currentMode;
}