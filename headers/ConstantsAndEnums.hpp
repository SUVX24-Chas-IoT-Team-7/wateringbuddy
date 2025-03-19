#ifndef MOIST_CONSTANTS_AND_ENUMS_HPP
#define MOIST_CONSTANTS_AND_ENUMS_HPP

enum thresholdNames {
    DRY,
    GOOD,
    WET
  };


  namespace moisture {
    // sensor pins
    const int powerPin = A0;
    const int readingPin = A1;
    // LED pins
    const int redPin = 6;
    const int yellowPin = 7;
    const int greenPin = 8;
    const int bluePin = 9;
    const int ledPins[] = { redPin, yellowPin, greenPin, bluePin };
  
    int thresholds[] = {25, 50, 70 };
  
    int lastReading = 0;
    int rawReading = 0;
    int percent = 0;
  
  } // moisture

  namespace uvsensor {
    const int readingPin = A2;
    int rawReading = 0;
    int prevRawReading = rawReading;
    float percent = 0;
    int thresholds[] = {120, 1000};
  } // uvsensor
  

#endif