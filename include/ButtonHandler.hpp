#ifndef BUTTON_HANDLER_HPP
#define BUTTON_HANDLER_HPP

class ButtonHandler
{
private:
    int buttonPin;
    bool lastButtonState;
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 50; // Milliseconds

public:
    ButtonHandler(int pin) : buttonPin(pin), lastButtonState(HIGH), lastDebounceTime(0) {}

    void begin()
    {
        pinMode(buttonPin, INPUT_PULLUP);
    }

    bool isPressed()
    {
        // Read the current state
        bool currentReading = digitalRead(buttonPin);
        bool buttonPressed = false;

        // Check if the button state has changed
        if (currentReading != lastButtonState)
        {
            // Reset the debounce timer
            lastDebounceTime = millis();
        }

        // If enough time has passed, check if the button is pressed
        if ((millis() - lastDebounceTime) > debounceDelay)
        {
            // Button is pressed (LOW due to pull-up resistor)
            if (currentReading == LOW && lastButtonState == HIGH)
            {
                buttonPressed = true;
            }
        }

        // Update the last state
        lastButtonState = currentReading;

        return buttonPressed;
    }
};

#endif