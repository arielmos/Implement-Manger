#ifndef IMPLEMENT_MANAGER_H_
#define IMPLEMENT_MANAGER_H_

#include <Arduino.h>

#include "implement.h"
#include "min_heap.h"
#include "menu.h"
#include "lcd.h"

// Simulation Constants
const double SIMULATION_TIME = 100;
const double TIME_STEP = 1e-2;
const double TIME_STEP_DELAY = 10;
const double FUEL_CONSUMPTION_RATE = 1;
const double FULL_FUEL_TANK = 10;

const int SPI_IMPLEMENTS = 1;
const int RS232_IMPLEMENTS = 2;

const int MAX_IMPLEMENT_COUNT = 10;

class ImplementManager
{
  Implement* m_implements[MAX_IMPLEMENT_COUNT];
  int m_implementCount;
  MinHeap m_eventQueue;
  double m_currentTime;

  Menu* m_menuInterface;

  ImplementManager() : m_implementCount(0), m_eventQueue(10), m_currentTime(0.0)
  {
    myLcd* lcdInstance = new myLcd(LCD_ROWS, LCD_ROWS, LCD_DELAY);
    m_menuInterface = new Menu(menuItems, numMenuItems, lcdInstance);
  }

public:
  static ImplementManager& getInstance()
  {
    static ImplementManager instance;
    return instance;
  }

  // Delete copy constructor and assignment operator to enforce singleton
  ImplementManager(const ImplementManager&) = delete;
  void operator=(const ImplementManager&) = delete;

  void setup();

  Implement* getImplements(int index){return m_implements[index];};
  int getImplementCount()const{return m_implementCount;};
  Menu* getMenuInterface() const{return m_menuInterface;};
  double getCurrentTime()const{return m_currentTime;};
  
  void setCurrentTime(double time){m_currentTime = time;};
  
  void addImplement(Implement* implement);
  void initializeSimulation();
  void runSimulation();

  void scheduleTurnOnEvent(int implementId);
  void scheduleFuelConsumptionEvent(int implementId, double fuelConsumptionTime);
  void scheduleFuelEmptyEvent(int implementId, double fuelEmptyTime);
  void scheduleExternalTriggerEvent(int implementId, bool state, double triggerTime);
  void scheduleTelemetryEvent(int implementId, double telemetryTime);

  void processTurnOn(Implement* implement, Event& currentEvent);
  void processFuelConsumption(Implement* implement, Event& currentEvent);
  void processFuelEmpty(Implement* implement, Event& currentEvent);
  void processExternalTrigger(Implement* implement, Event& currentEvent);
  void processTelemetry(Implement* implement, double telemetryTime);
};

#endif /* IMPLEMENT_MANAGER_H_ */
