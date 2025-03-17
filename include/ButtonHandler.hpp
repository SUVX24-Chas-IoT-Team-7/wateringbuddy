
#ifndef BUTTON_HANDLER_HPP
#define BUTTON_HANDLER_HPP
/**
 * @brief   Button Handler class to handle buttons
 * @details This class is used to handle the buttons. It reads the button state and debounces the button
 *       It has methods to check if the mode button, select button, up button and down button are pressed
 * @version 0.1
 * @date 2025-03-14
 */
class ButtonHandler
{
private:
    int modeButtonPin;   // Button to switch modes
    int selectButtonPin; // Button to select/cycle through thresholds
    int upButtonPin;     // Button to increase values
    int downButtonPin;   // Button to decrease values

    bool lastModeState;
    bool lastSelectState;
    bool lastUpState;
    bool lastDownState;

    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 50; // Milliseconds

public:
    ButtonHandler(int modePin, int selectPin, int upPin, int downPin)
        : modeButtonPin(modePin), selectButtonPin(selectPin),
          upButtonPin(upPin), downButtonPin(downPin),
          lastModeState(HIGH), lastSelectState(HIGH),
          lastUpState(HIGH), lastDownState(HIGH),
          lastDebounceTime(0) {}

    void begin()
    {
        pinMode(modeButtonPin, INPUT_PULLUP);
        pinMode(selectButtonPin, INPUT_PULLUP);
        pinMode(upButtonPin, INPUT_PULLUP);
        pinMode(downButtonPin, INPUT_PULLUP);
    }

    bool isModePressed()
    {
        return isButtonPressed(modeButtonPin, lastModeState);
    }

    bool isSelectPressed()
    {
        return isButtonPressed(selectButtonPin, lastSelectState);
    }

    bool isUpPressed()
    {
        return isButtonPressed(upButtonPin, lastUpState);
    }

    bool isDownPressed()
    {
        return isButtonPressed(downButtonPin, lastDownState);
    }

private:
    bool isButtonPressed(int pin, bool &lastState)
    {
        // Read the current state
        bool currentReading = digitalRead(pin);
        bool buttonPressed = false;

        // Check if the button state has changed
        if (currentReading != lastState)
        {
            // Reset the debounce timer
            lastDebounceTime = millis();
        }

        // If enough time has passed, check if the button is pressed
        if ((millis() - lastDebounceTime) > debounceDelay)
        {
            // Button is pressed (LOW due to pull-up resistor)
            if (currentReading == LOW && lastState == HIGH)
            {
                buttonPressed = true;
            }
        }

        // Update the last state
        lastState = currentReading;

        return buttonPressed;
    }
};

#endif