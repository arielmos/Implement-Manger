#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>

#include <LiquidCrystal.h>

// Define LCD pins
extern const unsigned int RS;
extern const unsigned int EN;
extern const unsigned int D4;
extern const unsigned int D5;
extern const unsigned int D6;
extern const unsigned int D7;

// Define LCD dimensions
extern const unsigned int LCD_COLUMNS;
extern const unsigned int LCD_ROWS;

extern const unsigned int LCD_DELAY;

class myLcd
{
  LiquidCrystal m_lcd;
  unsigned int m_lcdColumns;
  unsigned int m_lcdRows;
  unsigned int m_lcdDelay;
  
  public:
  myLcd(unsigned int cols, unsigned int rows, unsigned int lcdDelay);
  
  void setup(); // Initialize the LCD
  void clearLCD(); // Clear the LCD screen
  void printToLCD(unsigned int row, unsigned int col, const char* message);// Print a message to the LCD at a specified row and column
  void scrollMessage(const char* message, unsigned int delayTime);// Scroll a long message on the LCD
  void flashMessage(const char* message, unsigned int times, unsigned int onTime, unsigned int offTime);// Flashing a message on the LCD

};
#endif /* LCD_H_ */
