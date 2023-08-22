#include "implement_manager.h"
#include <SPI.h>

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
