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
class ThresholdManager
{
private:
    int veryWetThreshold = 200;
    int wetThreshold = 400;
    int moistThreshold = 600;
    int dryThreshold = 800;

    int currentThreshold = 0;

    int mode = 0;

public:
    ThresholdManager() {}

    void toggleMode()
    {
        mode = !mode;
        currentThreshold = 0;
    }

    int getMode() const
    {
        return mode;
    }

    void nextThreshold()
    {
        currentThreshold = (currentThreshold + 1) % 4;
    }

    const char *getCurrentThresholdName() const
    {
        switch (currentThreshold)
        {
        case 0:
            return "Very Wet";
        case 1:
            return "Wet";
        case 2:
            return "Moist";
        case 3:
            return "Dry";
        default:
            return "Unknown";
        }
    }

    int getCurrentThresholdValue() const
    {
        switch (currentThreshold)
        {
        case 0:
            return veryWetThreshold;
        case 1:
            return wetThreshold;
        case 2:
            return moistThreshold;
        case 3:
            return dryThreshold;
        default:
            return 0;
        }
    }

    void increaseThreshold(int amount = 10)
    {
        switch (currentThreshold)
        {
        case 0:
            veryWetThreshold += amount;
            if (veryWetThreshold >= wetThreshold)
                veryWetThreshold = wetThreshold - 10;
            break;
        case 1:
            wetThreshold += amount;
            if (wetThreshold >= moistThreshold)
                wetThreshold = moistThreshold - 10;
            break;
        case 2:
            moistThreshold += amount;
            if (moistThreshold >= dryThreshold)
                moistThreshold = dryThreshold - 10;
            break;
        case 3:
            dryThreshold += amount;
            if (dryThreshold > 1023)
                dryThreshold = 1023;
            break;
        }
    }

    void decreaseThreshold(int amount = 10)
    {
        switch (currentThreshold)
        {
        case 0:
            veryWetThreshold -= amount;
            if (veryWetThreshold < 0)
                veryWetThreshold = 0;
            break;
        case 1:
            wetThreshold -= amount;
            if (wetThreshold <= veryWetThreshold)
                wetThreshold = veryWetThreshold + 10;
            break;
        case 2:
            moistThreshold -= amount;
            if (moistThreshold <= wetThreshold)
                moistThreshold = wetThreshold + 10;
            break;
        case 3:
            dryThreshold -= amount;
            if (dryThreshold <= moistThreshold)
                dryThreshold = moistThreshold + 10;
            break;
        }
    }

    const char *getMoistureStatus(int moistureValue) const
    {
        if (moistureValue < veryWetThreshold)
        {
            return "Very Wet";
        }
        else if (moistureValue < wetThreshold)
        {
            return "Wet";
        }
        else if (moistureValue < moistThreshold)
        {
            return "Moist";
        }
        else if (moistureValue < dryThreshold)
        {
            return "Dry";
        }
        else
        {
            return "Very Dry";
        }
    }

    int getLEDPin(int moistureValue) const
    {
        if (moistureValue < veryWetThreshold)
        {
            return 12;
        }
        else if (moistureValue < wetThreshold)
        {
            return 11;
        }
        else if (moistureValue < moistThreshold)
        {
            return 10;
        }
        else if (moistureValue < dryThreshold)
        {
            return 9;
        }
        else
        {
            return 8;
        }
    }
};

#endif