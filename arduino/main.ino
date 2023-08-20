#include "implement_manager.h"

volatile bool newData = false;
String receivedStr;

ImplementManager& manager = ImplementManager::getInstance();
    
void setup()
{
  manager.setup();
  manager.initializeSimulation();
  manager.getMenuInterface()->display();
}

void loop()
{
  manager.runSimulation(); 
  manager.getMenuInterface()->activateAction();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    receivedStr += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') 
    {
      newData = true;
    }
  }
}
