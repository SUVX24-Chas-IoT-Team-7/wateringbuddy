/**
 * @file Timer.hpp
 * @author John Collinder & Erik Dahl
 * @brief  Timer class to handle timing
 * @details  This class is used to handle timing tasks
 * It has methods to reset the timer, check if it is time to update and set the duration
 * @version 0.1
 * @date 2025-03-20
 */
#ifndef TIMER_HPP
#define TIMER_HPP
#include <Arduino.h>

/**
 * @brief This class is used to handle timing tasks
 * 
 */
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
    void setDuration(unsigned long duration = 10000)
    {
        m_timerDuration = duration;
    }
};

#endif // TIME_Timer_HPP