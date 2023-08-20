#include "menu.h"
#include "implement_manager.h"

// Define menu items
MenuItem menuItems[] = {
    {1, "Get Status", actionOption1},
    {2, "External Trigger", actionOption2},
    {3, "Turn on implement 3", actionOption3},
};

const int numMenuItems = sizeof(menuItems) / sizeof(menuItems[0]);

Menu::Menu(MenuItem* items, int itemCount, myLcd* lcd):m_menuItems(items), m_numMenuItems(itemCount), m_lcdInterface(lcd){}

void Menu::display()
{
    Serial.println("================ Menu ================");
    for (int i = 0; i < m_numMenuItems; i++)
    {
        Serial.print(m_menuItems[i].index);
        Serial.print(": ");
        Serial.println(m_menuItems[i].description);
    }
    Serial.println("======================================");
}

void Menu::activateAction()
{
    static bool chooseImplement = false;
    if (newData)
    {
        String userInput = receivedStr;
        newData = false;
        receivedStr = "";

        int index = userInput.toInt();
        
        if(chooseImplement)
        {
          ImplementManager& manager = ImplementManager::getInstance();

          chooseImplement = false;
          if(0 <= index && index < manager.getImplementCount())
          {
            using FunctionPtrType2 = void(*)(Menu& menu, int id);
            FunctionPtrType2 action2 = reinterpret_cast<FunctionPtrType2>(menuItems[1].action);
            action2(*this, index);
          }
          else
          {
            Serial.println("Invalid input. Please select a valid option.");
          }
        }
        else if(0 < index && index <= numMenuItems)
        {
          if(index == 2  && !chooseImplement)
          {
            chooseImplement = true;
            Serial.println("Choose Implement:");
            return;
          }
          using FunctionPtrType1 = void(*)(Menu& menu);
          FunctionPtrType1 action1 = reinterpret_cast<FunctionPtrType1>(menuItems[index - 1].action);
          action1(*this);
        }
        else
        {
          Serial.println("Invalid input. Please select a valid option.");
        }
        display();
    }
}

// Menu action functions

void actionOption1(Menu& menu)
{
    Serial.println("Executing Option 1");
    
    menu.getLcdInterface()->clearLCD();
    delay(lcdDelay);
    menu.getLcdInterface()->printToLCD(0, 0, menu.getMenuItems()[0].description);
    delay(lcdDelay);
    menu.getLcdInterface()->clearLCD();
    delay(lcdDelay);

    ImplementManager& manager = ImplementManager::getInstance();

    for (int i = 0; i < manager.getImplementCount(); i++)
    {
        manager.scheduleTelemetryEvent(manager.getImplements(i)->getId(), manager.getCurrentTime());
    }
}

void actionOption2(Menu& menu, int id)
{
    Serial.println("Executing Option 2");
    
    menu.getLcdInterface()->clearLCD();
    delay(lcdDelay);
    menu.getLcdInterface()->printToLCD(0, 0, menu.getMenuItems()[1].description);
    delay(lcdDelay);
    menu.getLcdInterface()->clearLCD();
    delay(lcdDelay);

    ImplementManager& manager = ImplementManager::getInstance();

    manager.scheduleExternalTriggerEvent(manager.getImplements(id)->getId(), manager.getImplements(id)->getState() ^ 1, manager.getCurrentTime());
}

void actionOption3()
{
    Serial.println("Executing Option 3");
    // Add your action code here
}
