#ifndef MENU_H_
#define MENU_H_

#include <Arduino.h>
#include "lcd.h"

struct MenuItem {
    const int index;
    const char* description;
    void (*action)();
};

extern MenuItem menuItems[];
extern const int numMenuItems;
extern volatile bool newData;
extern String receivedStr;

// Menu module
class Menu {
    MenuItem* m_menuItems;
    int m_numMenuItems;
    myLcd* m_lcdInterface;
public:
    Menu(MenuItem* items, int itemCount, myLcd* lcd);
    void display();
    void activateAction();
    MenuItem* getMenuItems()const{return m_menuItems;}
    myLcd* getLcdInterface()const{return m_lcdInterface;}
};

// Function prototypes for menu actions
void actionOption1(Menu& menu);
void actionOption2(Menu& menu, int id);
void actionOption3();

#endif /* MENU_H_ */
