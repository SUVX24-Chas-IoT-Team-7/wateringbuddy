#ifndef TIMER_HPP
#define TIMER_HPP
#include <Arduino.h>
// Skapa en timer för att stänga av LCD efter 10 sekunder
// Skapa en timer åt WATERING_DISPLAY så att den uppdateras konstant medans dem andra sidorna inte gör det.
class Timer
{
private:
    unsigned long m_timerDuration;
    unsigned long m_lastUpdate;

public:
    Timer(unsigned long timerDuration = 10000)  
        : m_timerDuration(timerDuration)
    {
        reset();
    }

    void reset()
    {
        m_lastUpdate = millis();
    }

    bool timeToUpdate()
    {
        return (millis() - m_lastUpdate > m_timerDuration);
    }

    void setDuration(unsigned long duration = 10000)
    {
        m_timerDuration = duration;
    }
};


#endif // TIME_Timer_HPP