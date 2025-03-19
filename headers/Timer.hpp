#ifndef TIMER_HPP
#define TIMER_HPP
#include <Arduino.h>
// Skapa en timer för att stänga av LCD efter 10 sekunder
// Skapa en timer åt WATERING_DISPLAY så att den uppdateras konstant medans dem andra sidorna inte gör det.
class Timer
{
private:
    unsigned long _timerDuration;
    unsigned long _lastUpdate;

public:
    Timer(unsigned long timerDuration = 10000)  
        : _timerDuration(timerDuration)
    {
        reset();
    }

    void reset()
    {
        _lastUpdate = millis();
    }

    bool timeToUpdate()
    {
        return (_lastUpdate - millis() > _timerDuration);
    }

    void setDuration(unsigned long duration = 10000)
    {
        _timerDuration = duration;
    }
};


#endif // TIME_Timer_HPP