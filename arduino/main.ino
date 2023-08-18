#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>

#include "lcd.h"
#include "menu.h"

Menu menuInstance(menuItems, numMenuItems);
myLcd lcdInstance(lcdColumns, lcdRows);

ThreadController controll;
Thread menuThread;
Thread lcdThread;

void menuWrapper(){menuInstance.run();}
void lcdWrapper(){lcdInstance.run();}

void setup()
{
  lcdInstance.lcdSetup();
  Serial.begin(9600);

  menuThread.onRun(menuWrapper);
  lcdThread.onRun(lcdWrapper);

  menuThread.setInterval(100);
  lcdThread.setInterval(100);

  // Adds both threads to the controller
  controll.add(&menuThread);
  controll.add(&lcdThread);
}

void loop() 
{
  controll.run();
}
