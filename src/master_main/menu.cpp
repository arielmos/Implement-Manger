#include "menu.h"
#include "implement_manager.h"

// Define menu items
MenuItem menuItems[] =
{
    {1, "Get Status"},
    {2, "External Trigger"}
};

const unsigned int numMenuItems = sizeof(menuItems) / sizeof(menuItems[0]);

Menu::Menu(MenuItem* items, unsigned int itemCount, myLcd* lcd)
          : m_menuItems(items), m_numMenuItems(itemCount), m_lcdInterface(lcd){}

void Menu::display()
{
    Serial.println("================ Menu ================");
    for (unsigned int i = 0; i < m_numMenuItems; i++)
    {
        Serial.print(m_menuItems[i].index);
        Serial.print(": ");
        Serial.println(m_menuItems[i].description);
    }
    Serial.println("======================================");
    Serial.println();
}

void Menu::activateAction()
{
  static bool chooseImplement = false;
  
  if (newData)
  {
    String userInput = receivedStr;
    newData = false;
    receivedStr = "";
  
    unsigned int action, id;
    
    if(chooseImplement)
    {
      action = m_menuItems[1].index;
      id = userInput.toInt();
    }
    else
    {
      action = userInput.toInt();
    }
            
    switch(action)
    {
      case 1:
        actionOption1();
        break;
      
      case 2:
        if(chooseImplement)
        {
          ImplementManager& manager = ImplementManager::getInstance();

          if(0 <= id && id < manager.getImplementCount())
          {
            String buf = "Implement Id: " + String(id) + " has been chosen to be toggle\n";
            Serial.println(buf);
            actionOption2(id);
          }
          else
          {
            Serial.println("Invalid Implement. Please select a valid option.");
          }
          chooseImplement = false;
        }
        else
        {
          chooseImplement = true;
          Serial.println("--------- Choose Implement: ----------");
        }
        break;
      
      default:
        Serial.println("Invalid input. Please select a valid option.");
        break;
    }
    if(!chooseImplement)
    {
      display();
    }
  }
}

// Menu action functions

void Menu::actionOption1()
{
    Serial.println("--------- Executing Option 1 ---------\n");
    
    getLcdInterface()->clearLCD();
    getLcdInterface()->printToLCD(0, 0, getMenuItems()[0].description);
    getLcdInterface()->clearLCD();

    ImplementManager& manager = ImplementManager::getInstance();

    for (unsigned int i = 0; i < manager.getImplementCount(); i++)
    {
        manager.scheduleTelemetryEvent(manager.getImplements(i)->getId(), manager.getCurrentTime());
    }
}

void Menu::actionOption2(unsigned int id)
{
    Serial.println("--------- Executing Option 2 ---------\n");

    getLcdInterface()->clearLCD();
    getLcdInterface()->printToLCD(0, 0, getMenuItems()[1].description);
    getLcdInterface()->clearLCD();

    ImplementManager& manager = ImplementManager::getInstance();

    manager.scheduleExternalTriggerEvent(manager.getImplements(id)->getId(), manager.getImplements(id)->getState() ^ true, manager.getCurrentTime());
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
