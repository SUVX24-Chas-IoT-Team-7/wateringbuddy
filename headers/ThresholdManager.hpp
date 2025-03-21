#ifndef THRESHOLD_MANAGER_HPP
#define THRESHOLD_MANAGER_HPP
/**
 * @file ThresholdManager.hpp
 * @author John Collinder(john.collinder@gmail.com) & Erik Dahl
 * @version 0.1
 * @date 2025-03-20
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
    /**
     * @brief Construct a new Threshold Manager object
     * @param moistureCenter
     */
    ThresholdManager(int moistureCenter = 60);

    /**
     * @brief Set Thresholds values
     * @param newMoistureCenter accepted values 35-85
     */
    void setNewThresholds(int newMoistureCenter);

    /**
     * @brief Get the Moisture Center Value object
     *
     * @return int
     */
    int getMoistureCenterValue() const;

    /**
     * @brief  increase the Threshold Value object
     */
    void increaseThreshold();

    /**
     * @brief  Decrease the Threshold Value object
     *
     */
    void decreaseThreshold();

    /**
     * @brief Get a string describing the given moistureValue
     *
     * @param moistureValue
     * @return const char*
     */
    const char *getMoistureString(int moistureValue) const;

        /**
     * @brief Get a short string describing the given moistureValue
     *
     * @param moistureValue
     * @return const char*
     */
    const char *getMoistureShortString(int moistureValue) const;

    /**
     * @brief
     *
     * @param moistureValue
     * @return int
     */
    int getLEDPin(int moistureValue) const;
};

#endif