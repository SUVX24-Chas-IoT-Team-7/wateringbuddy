#include "Buttons.hpp"



bool Button::pressDetected(){
    return (m_currentState && !m_lastState);
}

bool Button::releaseDetected(){
    return (!m_currentState && m_lastState);
}

Button::Button(int pin, PinMode pinMode, time_t longPressTime) 
    : m_longPressTime { longPressTime }, m_pin { pin, pinMode } {}

void Button::init() {
    m_pin.init();
}

ButtonState Button::getState() {
    m_currentState = m_pin.read(Pin::DIGITAL).value_or(0);

    if (pressDetected()){
        m_awaitingLongpress = true;
        m_pressTime = millis();
    }

    time_t currentTime = millis();

    if (releaseDetected() && (millis() - m_pressTime > debounceTime)) {
        m_isPressed = false;
        m_awaitingLongpress = false;

        if (currentTime - m_pressTime < m_longPressTime) {
            m_lastState = m_currentState;      
            return SHORTPRESS;
        }    
    }

    if (m_awaitingLongpress && (currentTime - m_pressTime > m_longPressTime)) {
        m_awaitingLongpress = false;
        return LONGPRESS;
    }
    
    m_lastState = m_currentState;
    return NOPRESS;
}