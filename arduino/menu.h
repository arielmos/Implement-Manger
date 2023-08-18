#ifndef MENU_H_
#define MENU_H_

#include <Arduino.h>

struct MenuItem {
    const int index;
    const char* description;
    void (*action)();
};

// Menu module
class Menu {
    MenuItem* m_menuItems;
    int m_numMenuItems;
public:
    Menu(MenuItem* items, int itemCount);
    void display();
    String getUserInput();
    void run();
};

// Function prototypes for menu actions
void actionOption1();
void actionOption2();
void actionOption3();

extern MenuItem menuItems[];
extern const int numMenuItems;
#endif /* MENU_H_ */
