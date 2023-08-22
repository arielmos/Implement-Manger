#include "lcd.h"

// Define LCD pins
const unsigned int RS = 9;
const unsigned int EN = 8;
const unsigned int D4 = 6;
const unsigned int D5 = 5;
const unsigned int D6 = 4;
const unsigned int D7 = 3;

// Define LCD dimensions
const unsigned int LCD_COLUMNS = 16;
const unsigned int LCD_ROWS = 2;

const unsigned int LCD_DELAY = 800;

myLcd::myLcd(unsigned int cols, unsigned int rows, unsigned int lcdDelay)
            : m_lcd(RS, EN, D4, D5, D6, D7),m_lcdColumns(cols), m_lcdRows(rows), m_lcdDelay(lcdDelay){};

void myLcd::setup()
{
  m_lcd.begin(m_lcdColumns, m_lcdRows);
  m_lcd.clear();
}

void myLcd::clearLCD()
{
  m_lcd.clear();
  delay(m_lcdDelay);
}

void myLcd::printToLCD(unsigned int row, unsigned int col, const char* message)
{
  m_lcd.setCursor(col, row);
  m_lcd.print(message);
  delay(m_lcdDelay);
}

void myLcd::scrollMessage(const char* message, unsigned int delayTime)
{
  unsigned int messageLen = strlen(message);
  for (unsigned int i = 0; i <= messageLen - m_lcdColumns; i++)
  {
    m_lcd.clear();
    m_lcd.setCursor(0, 0);
    m_lcd.print(message + i);
    delay(delayTime);
  }
}

void myLcd::flashMessage(const char* message, unsigned int times, unsigned int onTime, unsigned int offTime) {
  for (unsigned int i = 0; i < times; i++)
  {
    m_lcd.clear();
    m_lcd.print(message);
    delay(onTime);
    m_lcd.clear();
    delay(offTime);
  }
}
