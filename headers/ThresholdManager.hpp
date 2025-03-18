#ifndef THRESHOLD_MANAGER_HPP
#define THRESHOLD_MANAGER_HPP
/**
 * @brief  Threshold Manager class to handle thresholds
 * @details
 * This class is used to handle the thresholds for the soil moisture sensor
 * It has methods to toggle between modes, select thresholds, increase and decrease thresholds
 * It also has methods to get the current threshold value and name
 * It has methods to get the moisture status and LED pin based on the moisture value
 */

#include "ConstantsAndEnums.hpp"
#include <algorithm>

 class ThresholdManager
{
private:
    int m_moistureCenter;
    int m_thresholds[3];

public:
    ThresholdManager(int moistureCenter = 60) 
        : m_moistureCenter { moistureCenter } 
        {
            setNewThresholds(m_moistureCenter);
        }

    /**
     * @brief Set Thresholds values
     * 
     * @param newMoistureCenter accepted values 35-85
     */
    void setNewThresholds(int newMoistureCenter) {
        if (newMoistureCenter >= 35 && newMoistureCenter <= 85 ) {
            m_thresholds[DRY] =  std::max(16, (int)(newMoistureCenter * 0.42)); 
            m_thresholds[GOOD] = newMoistureCenter - 10;
            m_thresholds[WET] = std::min(90, newMoistureCenter + 10);
        }
    }


    int getMoistureCenterValue() const
    {
        return m_moistureCenter;
    }

    void increaseThreshold()
    {

        if (m_moistureCenter < 85) {
            // update center value
            m_moistureCenter++;
            // update other threshold values
            setNewThresholds(m_moistureCenter);
        }
    }

    void decreaseThreshold()
    {
        if (m_moistureCenter > 35) {
            // update center value
            m_moistureCenter--;
            // update other threshold values
            setNewThresholds(m_moistureCenter);
        }
    }

    char* getMoistureString(int moistureValue) const
    {
        if (moistureValue < m_thresholds[DRY])
        {
            return "Dry";
        }
        else if (moistureValue < m_thresholds[GOOD])
        {
            return "Semidry";
        }
        else if (moistureValue < m_thresholds[WET])
        {
            return "Good!";
        }
        else
        {
            return "Wet :-(";
        }
    }

    int getLEDPin(int moistureValue) const
    {
        if (moistureValue < m_thresholds[DRY])
        {
            return moisture::redPin;
        }
        else if (moistureValue < m_thresholds[GOOD])
        {
            return moisture::yellowPin;
        }
        else if (moistureValue < m_thresholds[WET])
        {
            return moisture::greenPin;
        }
        else
        {
            return moisture::bluePin;
        }
    }
};

#endif