#ifndef MENU_H_
#define MENU_H_

#include <Arduino.h>

#include "lcd.h"

struct MenuItem {
    const int index;
    const char* description;
};

extern MenuItem menuItems[];
extern const int numMenuItems;

extern volatile bool newData;
extern String receivedStr;

class Menu
{
    MenuItem* m_menuItems;
    int m_numMenuItems;
    myLcd* m_lcdInterface;
public:
    Menu(MenuItem* items, int itemCount, myLcd* lcd);
    
    void display();
    
    MenuItem* getMenuItems()const{return m_menuItems;}
    myLcd* getLcdInterface()const{return m_lcdInterface;}

    void activateAction();
    void actionOption1();
    void actionOption2(int id);
};

void serialEvent();

#endif /* MENU_H_ */
