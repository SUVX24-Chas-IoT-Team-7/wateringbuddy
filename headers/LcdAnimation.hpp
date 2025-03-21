/**
 * @file LcdAnimation.hpp
 * @author Erik Dahl (erik@iunderlandet.se)
 * @brief A short animation to make startup more fun to the user
 * @version 0.1
 * @date 2025-03-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __WB_LCD_ANIMATION_HPP__
#define __WB_LCD_ANIMATION_HPP__
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

/**
 * @brief The function runs an animation of the words WATERING BUDDY
 * 
 * Note that it is really crude implementation using delay. It is only 
 * intended for running once before program starts. 
 * So do not try to use it in the loop since it will interfere with timing
 *
 * @param lcd 
 */
void runLcdAnimation(LiquidCrystal_I2C& lcd);

#endif