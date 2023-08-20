#include "lcd.h"

// Define LCD pins
const int rs = 9;
const int en = 8;
const int d4 = 6;
const int d5 = 5;
const int d6 = 4;
const int d7 = 3;

// Define LCD dimensions
const int lcdColumns = 16;
const int lcdRows = 2;

const int lcdDelay = 1000;

myLcd::myLcd(int cols, int rows):m_lcd(rs, en, d4, d5, d6, d7),m_lcdColumns(cols), m_lcdRows(rows){};

// Initialize the LCD
void myLcd::lcdSetup()
{
  m_lcd.begin(m_lcdColumns, m_lcdRows);
  m_lcd.clear();
}

// Clear the LCD screen
void myLcd::clearLCD()
{
  m_lcd.clear();
}

// Print a message to the LCD at a specified row and column
void myLcd::printToLCD(int row, int col, const char* message)
{
  m_lcd.setCursor(col, row);
  m_lcd.print(message);
}

// Scroll a long message on the LCD
void myLcd::scrollMessage(const char* message, int delayTime)
{
  int messageLen = strlen(message);
  for (int i = 0; i <= messageLen - m_lcdColumns; i++)
  {
    m_lcd.clear();
    m_lcd.setCursor(0, 0);
    m_lcd.print(message + i);
    delay(delayTime);
  }
}

// Example of flashing a message on the LCD
void myLcd::flashMessage(const char* message, int times, int onTime, int offTime) {
  for (int i = 0; i < times; i++)
  {
    m_lcd.clear();
    m_lcd.print(message);
    delay(onTime);
    m_lcd.clear();
    delay(offTime);
  }
}
