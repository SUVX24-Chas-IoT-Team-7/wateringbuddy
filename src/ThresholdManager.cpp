#include "ThresholdManager.hpp"

ThresholdManager::ThresholdManager(int moistureCenter = 60)
    : m_moistureCenter{moistureCenter}
{
    setNewThresholds(m_moistureCenter);
}

/**
 * @brief Set Thresholds values
 * @param newMoistureCenter accepted values 35-85
 */
void ThresholdManager::setNewThresholds(int newMoistureCenter)
{
    if (newMoistureCenter >= 35 && newMoistureCenter <= 85)
    {
        m_thresholds[DRY] = std::max(16, (int)(newMoistureCenter * 0.42));
        m_thresholds[GOOD] = newMoistureCenter - 10;
        m_thresholds[WET] = std::min(90, newMoistureCenter + 10);
    }
}
/**
 * @brief Get the Moisture Center Value object
 *
 * @return int
 */
int ThresholdManager::getMoistureCenterValue() const
{
    return m_moistureCenter;
}
/**
 * @brief  increase the Threshold Value object
 */
void ThresholdManager::increaseThreshold()
{
    if (m_moistureCenter < 85)
    {
        // update center value
        m_moistureCenter++;
        // update other threshold values
        setNewThresholds(m_moistureCenter);
    }
}
/**
 * @brief  Decrease the Threshold Value object
 *
 */
void ThresholdManager::decreaseThreshold()
{
    if (m_moistureCenter > 35)
    {
        // update center value
        m_moistureCenter--;
        // update other threshold values
        setNewThresholds(m_moistureCenter);
    }
}
/**
 * @brief Get the Moisture String object
 *
 * @param moistureValue
 * @return const char*
 */
const char *ThresholdManager::getMoistureString(int moistureValue) const
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
/**
 * @brief
 *
 * @param moistureValue
 * @return int
 */
int ThresholdManager::getLEDPin(int moistureValue) const
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
