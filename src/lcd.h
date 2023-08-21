#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>

#include <LiquidCrystal.h>

// Define LCD pins
extern const int RS;
extern const int EN;
extern const int D4;
extern const int D5;
extern const int D6;
extern const int D7;

// Define LCD dimensions
extern const int LCD_COLUMNS;
extern const int LCD_ROWS;

extern const int LCD_DELAY;

class myLcd
{
  LiquidCrystal m_lcd;
  int m_lcdColumns;
  int m_lcdRows;
  int m_lcdDelay;
  
  public:
  myLcd(int cols, int rows, int lcdDelay);
  
  void setup(); // Initialize the LCD
  void clearLCD(); // Clear the LCD screen
  void printToLCD(int row, int col, const char* message);// Print a message to the LCD at a specified row and column
  void scrollMessage(const char* message, int delayTime);// Scroll a long message on the LCD
  void flashMessage(const char* message, int times, int onTime, int offTime);// Flashing a message on the LCD

};
#endif /* LCD_H_ */
