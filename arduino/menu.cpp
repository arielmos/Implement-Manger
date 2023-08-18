#include "menu.h"

// Define menu items
MenuItem menuItems[] = {
    {1, "Option 1", actionOption1},
    {2, "Option 2", actionOption2},
    {3, "Option 3", actionOption3},
};

const int numMenuItems = sizeof(menuItems) / sizeof(menuItems[0]);

Menu::Menu(MenuItem* items, int itemCount):m_menuItems(items), m_numMenuItems(itemCount){}

void Menu::display() {
    Serial.println("Menu:");
    for (int i = 0; i < m_numMenuItems; i++)
    {
        Serial.print(m_menuItems[i].index);
        Serial.print(": ");
        Serial.println(m_menuItems[i].description);
    }
    Serial.println();
}

unsigned long lastInputCheckTime = 0;
const unsigned long inputCheckInterval = 200; // Check for input every 200 milliseconds

String Menu::getUserInput()
{
    unsigned long currentTime = millis();
    // Check for user input every inputCheckInterval milliseconds
    if (currentTime - lastInputCheckTime >= inputCheckInterval)
    {
      lastInputCheckTime = currentTime;
      
      if(!Serial.available())
      {
          return Serial.readStringUntil('\n');
      }

    }
    return "";
}

void Menu::run()
{
    display();
    String userInput;

    while (true)
    {
        userInput = getUserInput();
        
        if(userInput == "")
        {
          continue;
        }

        int index = userInput.toInt();

        if(0 < index && index <= numMenuItems)
        {
          menuItems[index - 1].action();
          break;
        }
        else
        {
          Serial.println("Invalid input. Please select a valid option.");
          display();
        }
    }
}

// Menu action functions

void actionOption1() {
    Serial.println("Executing Option 1");
    // Add your action code here
}

void actionOption2() {
    Serial.println("Executing Option 2");
    // Add your action code here
}

void actionOption3() {
    Serial.println("Executing Option 3");
    // Add your action code here
}
