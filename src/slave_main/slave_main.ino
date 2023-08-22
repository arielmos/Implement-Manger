#include "lcd.h"
#include "spi_implement.h"

char buff[50];
volatile byte indx;
volatile boolean process;
const SPIImplement spiImplement(SS_PIN);
myLcd* lcdInstance = new myLcd(LCD_ROWS, LCD_ROWS, LCD_DELAY);

void setup() {
  Serial.begin(9600);
  spiImplement.setup();
  lcdInstance->setup();
  lcdInstance->printToLCD(0, 0, "State:Off");
  lcdInstance->printToLCD(1, 0, "Fuel:");
}

void loop()
{
  if (process)
  {
    process = false; //reset the process
    spiImplement.handlePrint();
    indx= 0; //reset button to zero
  }
  delay(100);
}
