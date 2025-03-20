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
    unsigned long _timerDuration;
    unsigned long _lastUpdate;

public:
    /**
     * @brief Construct a new Timer object
     * @param timerDuration
     */
    Timer(unsigned long timerDuration = 10000);
    /**
     * @brief  Reset the timer
     */
    void reset()
    {
        _lastUpdate = millis();
    }
    /**
     * @brief  Check if it is time to update
     * @return true
     * @return false
     */
    bool timeToUpdate()
    {
        return (_lastUpdate - millis() > _timerDuration);
    }
    /**
     * @brief Set the Duration object
     * @param duration
     */
    void setDuration(unsigned long duration = 10000)
    {
        _timerDuration = duration;
    }
};
/**
 * @brief Construct a new Timer:: Timer object
 * @param timerDuration
 */
Timer::Timer(unsigned long timerDuration)
    : _timerDuration(timerDuration)
{
    reset();
}

#endif // TIME_Timer_HPP