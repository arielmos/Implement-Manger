#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <LiquidCrystal.h>

/* The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// Define LCD pins
extern const int rs;
extern const int en;
extern const int d4;
extern const int d5;
extern const int d6;
extern const int d7;

// Define LCD dimensions
extern const int lcdColumns;
extern const int lcdRows;

class myLcd{
  LiquidCrystal m_lcd;
  int m_lcdColumns;
  int m_lcdRows;
  
  public:
  myLcd(int cols, int rows);
  // Initialize the LCD
  void lcdSetup();

  // Clear the LCD screen
  void clearLCD();

  // Print a message to the LCD at a specified row and column
  void printToLCD(int row, int col, const char* message);

  // Scroll a long message on the LCD
  void scrollMessage(const char* message, int delayTime);
  
  // Example of flashing a message on the LCD
  void flashMessage(const char* message, int times, int onTime, int offTime);

  void run();
};
#endif /* LCD_H_ */
