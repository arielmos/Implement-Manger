#include "spi_implement.h"

const unsigned int SCK_PIN = 13;
const unsigned int MISO_PIN = 12;
const unsigned int MOSI_PIN = 11;
const unsigned int SS_PIN = 10;

void SPIImplement::setState(bool state)
{
  m_state = state;
  m_state ? sendString("aOn ") : sendString("aOff");
}
void SPIImplement::setFuelLevel(double level)
{
  static unsigned int count = 0;
  m_fuelLevel = level;

  if(count % 20 == 0)
  {
    String buf = "b" + String(m_fuelLevel);
    sendString(buf);
  }
  count++;
}

void SPIImplement::setup()
{
  pinMode(m_ssPin, OUTPUT);
  digitalWrite(m_ssPin, HIGH); // Deselect the slave initially
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
}

byte SPIImplement::send(byte data)
{
  digitalWrite(m_ssPin, LOW); // Select the slave
  byte receivedData = SPI.transfer(data); // Send and receive data simultaneously
  digitalWrite(m_ssPin, HIGH); // Deselect the slave
  return receivedData;
}

String SPIImplement::sendString(const String &data)
{
  digitalWrite(m_ssPin, LOW); // Select the slave
  String receivedData;
  
  for(unsigned int i =0; i < data.length(); i++ )
  {
    char c = data[i];
    receivedData += static_cast<char>(SPI.transfer(c)); // Send and receive each character
  }
  SPI.transfer('\r');
  
  digitalWrite(m_ssPin, HIGH); // Deselect the slave
  delay(2000);
  return receivedData;
}

byte SPIImplement::receive()
{
  return send(0x00); // Send a dummy byte to receive data
}
