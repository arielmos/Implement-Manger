#include "lcd.h"

// Define LCD pins
const int RS = 9;
const int EN = 8;
const int D4 = 6;
const int D5 = 5;
const int D6 = 4;
const int D7 = 3;

// Define LCD dimensions
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

const int LCD_DELAY = 800;

myLcd::myLcd(int cols, int rows, int lcdDelay)
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

void myLcd::printToLCD(int row, int col, const char* message)
{
  m_lcd.setCursor(col, row);
  m_lcd.print(message);
  delay(m_lcdDelay);
}

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
