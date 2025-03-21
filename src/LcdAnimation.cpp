#include "LcdAnimation.hpp"

void runLcdAnimation(LiquidCrystal_I2C& lcd){
    const char aniLine1[8] = { 'W','A','T','E','R','I','N','G'};
    const char aniLine2[5] = { 'B','U','D','D','Y' };
    lcd.clear();
    // animate first line
    lcd.setCursor(0,0);
    for (const char letter : aniLine1) {
      lcd.print(letter);
      lcd.print(' ');
      delay(250);
    }
    // animate second line
    lcd.setCursor(3,1);
    for (const char letter : aniLine2) {
      lcd.print(letter);
      lcd.print(' ');
      delay(250);
    }
    // wait 1.25 seconds before clearing screen
      delay(1250);
      lcd.clear();
  
  }