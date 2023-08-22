#include "spi_implement.h"

const unsigned int SCK_PIN = 13;
const unsigned int MISO_PIN = 12;
const unsigned int MOSI_PIN = 11;
const unsigned int SS_PIN = 10;

void SPIImplement::setup()
{
  Serial.println("======================================");
  Serial.println("============= SPI Slave ==============");
  Serial.println("======================================");

  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE); // turn on SPI in slave mode
  indx = 0; // buffer empty
  process = false;
  SPI.attachInterrupt(); // turn on interrupt
}

void SPIImplement::handlePrint()
{
  String str;
  if(buff[0] == 'a')
  {
    str = buff + 1;
    str.remove(str.length() - 1);
    
    while(str.length() > 3)
    {
      str.remove(str.length() - 1);
      
    }
    Serial.print("============= State: "); 
    Serial.print(str);
    Serial.println("============="); 
    lcdInstance->printToLCD(0, 6, "          ");
    lcdInstance->printToLCD(0, 6, str.c_str());
  }
  else if(buff[0] == 'b')
  {
    str = buff + 1;
    str.remove(str.length() - 1);
    str.remove(str.length() - 1);
    
    Serial.print("Fuel Level: "); 
    Serial.println(str); 
    lcdInstance->printToLCD(1, 5, str.c_str());
  }
}

ISR (SPI_STC_vect) // SPI interrupt routine 
{ 
   byte c = SPDR; // read byte from SPI Data Register
   if (indx < sizeof(buff))
   {
      buff[indx++] = c; // save data in the next index in the array buff
      if (c == '\r') //check for the end of the word
      process = true;
   }
}
