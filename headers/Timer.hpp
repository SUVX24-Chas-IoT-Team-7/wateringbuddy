#ifndef TIMER_HPP
#define TIMER_HPP
/**
 * @file Timer.hpp
 * @author John Collinder & Erik Dahl
 * @brief  Timer class to handle timing
 * @details  This class is used to handle timing for the LCD display
 * It has methods to reset the timer, check if it is time to update and set the duration
 * @version 0.1
 * @date 2025-03-20
 */
// Skapa en timer för att stänga av LCD efter 10 sekunder
// Skapa en timer åt WATERING_DISPLAY så att den uppdateras konstant medans dem andra sidorna inte gör det.
#include <Arduino.h>
class Timer
{

private:
    unsigned long m_timerDuration;
    unsigned long m_lastUpdate;

public:

    /**
     * @brief Construct a new Timer object
     * @param timerDuration
     */
    Timer(unsigned long timerDuration = 10000)  
        : m_timerDuration(timerDuration)
    {
        reset();
    }
  
    /**
     * @brief  Reset the timer
     */
    void reset()
    {
        m_lastUpdate = millis();
    }
    /**
     * @brief  Check if it is time to update
     * @return true
     * @return false
     */
    bool timeToUpdate()
    {
        return (millis() - m_lastUpdate > m_timerDuration);
    }

    /**
     * @brief Set the Duration object
     * @param duration
     */
    void setDuration(unsigned long duration = 3000) // change to longer value when done with debugging
    {
        m_timerDuration = duration;
    }
};

#endif // TIME_Timer_HPP