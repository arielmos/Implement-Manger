#include "implement_manager.h"
#include "spi_implement.h"
#include "rs232_implement.h"

void ImplementManager::addImplement(Implement* implement)
{
    if(m_implementCount < MAX_IMPLEMENT_COUNT)
    {
      implement->setId(m_implementCount);
      m_implements[m_implementCount++] = implement;
    }
}

void ImplementManager::setup()
{
  m_menuInterface->getLcdInterface()->setup();
  Serial.begin(9600);
}

void ImplementManager::initializeSimulation()
{
  Serial.println("======================================");
  Serial.println("Hello BlueWhite! Initialize Simulation");
  Serial.println("======================================\n");  

  m_menuInterface->getLcdInterface()->printToLCD(0, 0, "Hello BlueWhite!");
  m_menuInterface->getLcdInterface()->printToLCD(1, 0, "Init Simulation");
  m_menuInterface->getLcdInterface()->clearLCD();

  // Initialize implements
  Implement* rs232Implements = new RS232Implement[RS232_IMPLEMENTS];
  Implement* spiImplements = new SPIImplement[SPI_IMPLEMENTS](SS_PIN);

  for (unsigned int i = 0; i < SPI_IMPLEMENTS; i++)
  {
    addImplement(&spiImplements[i]);
  }

  for (unsigned int i = 0; i < RS232_IMPLEMENTS; i++)
  {
    addImplement(&rs232Implements[i]);
  }
   
  // Add initial turn-on events for each implement
  for (unsigned int i = 0; i < m_implementCount; i++)
  {
    scheduleTurnOnEvent(m_implements[i]->getId());
  }
}

void ImplementManager::runSimulation()
{ 
  while (!m_eventQueue.isEmpty())
  {
    Event currentEvent = m_eventQueue.top();
    m_eventQueue.pop();

    // Simulate the event's effects on the corresponding implement
    Implement* implement = m_implements[currentEvent.m_implementId];

    // Process Events
    switch (currentEvent.m_eventType)
    {
      case FuelConsumption:
        processFuelConsumption(implement, currentEvent);
        break;
        
      case TurnOn:
        processTurnOn(implement, currentEvent);
        break;

      case FuelEmpty:
        processFuelEmpty(implement, currentEvent);
        break;
  
      case ExternalTrigger:
        processExternalTrigger(implement, currentEvent);
        break;
  
      case Telemetry:
        processTelemetry(implement, currentEvent.m_time);
        break;
      
      default:
        break;
    }
  }

  static bool endSim = true;
  double currentTime = getCurrentTime();
//  Serial.print("currentTime = ");
//  Serial.println(currentTime);

  if(currentTime <= SIMULATION_TIME)
  {
    for (unsigned int i = 0; i < m_implementCount; i++)
    {
      if (m_implements[i]->getState())
      {
        scheduleFuelConsumptionEvent(m_implements[i]->getId(), getCurrentTime());
      }
    }

    // Update simulation time
    setCurrentTime(currentTime + TIME_STEP);
    delay(TIME_STEP_DELAY);
  }
  else if(endSim)
  {
    Serial.println("======== Simulation Finished =========");
    m_menuInterface->getLcdInterface()->printToLCD(0, 0, "== Simulation ==");
    m_menuInterface->getLcdInterface()->printToLCD(1, 0, "==== Finshed ===");
    endSim = false;
  }
}

void ImplementManager::processTurnOn(Implement* implement, Event& currentEvent)
{
  implement->setState(true);
  implement->setFuelLevel(FULL_FUEL_TANK);
  String buf = "ImplementManager::processTurnOn: Implement Id: " + String(implement->getId()) + " Turned On\n";
  Serial.println("=============== Event ================");
  Serial.println(buf);
}

void ImplementManager::processFuelConsumption(Implement* implement, Event& currentEvent)
{
  double timeDelta = getCurrentTime() - currentEvent.m_time;
  implement->setFuelLevel(implement->getFuelLevel() - FUEL_CONSUMPTION_RATE * timeDelta);

  if (implement->getFuelLevel() <= 0.0)
  {
    implement->setFuelLevel(0.0);
    scheduleFuelEmptyEvent(currentEvent.m_implementId, currentEvent.m_time);
  }
}

void ImplementManager::processFuelEmpty(Implement* implement, Event& currentEvent)
{
  implement->setState(false);
  String buf = "ImplementManager::processFuelEmpty: Implement Id: " + String(implement->getId()) + " Turned Off\n";
  Serial.println("=============== Event ================");
  Serial.println(buf);

  buf = "=== New Event ===";
  m_menuInterface->getLcdInterface()->flashMessage(buf.c_str(), 2, 500, 500);
  
  buf = "Event Time: " + String(currentEvent.m_time);
  m_menuInterface->getLcdInterface()->printToLCD(0, 0, buf.c_str());

  buf = "Implement Id: " + String(implement->getId());
  m_menuInterface->getLcdInterface()->printToLCD(1, 0, buf.c_str());

  m_menuInterface->getLcdInterface()->clearLCD();

  buf = "State: Off";
  m_menuInterface->getLcdInterface()->printToLCD(0, 0, buf.c_str());

  buf = "Fuel Tank Empty";
  m_menuInterface->getLcdInterface()->printToLCD(1, 0, buf.c_str());
  
  m_menuInterface->getLcdInterface()->clearLCD();
}

void ImplementManager::processExternalTrigger(Implement* implement, Event& currentEvent)
{
  implement->setState(currentEvent.m_state);

  String buf = "ImplementManager::processExternalTrigger: Event Time: " + String(currentEvent.m_time) +
               " Implement Id: " + String(implement->getId());
               
  buf += currentEvent.m_state ? " Turned On\n" : " Turned Off\n";

  Serial.println("=============== Event ================");
  Serial.println(buf);
}

void ImplementManager::processTelemetry(Implement* implement, double telemetryTime)
{
   String buf = "ImplementManager::processTelemetry: Event Time: " + String(telemetryTime) +
                " Implement Id: " + String(implement->getId()) + " State: " + String(implement->getState()) +
                " Fuel Level: " + String(implement->getFuelLevel()) + "\n";
                
  Serial.println("=============== Event ================");
  Serial.println(buf);

  buf = "=== New Event ===";
  m_menuInterface->getLcdInterface()->flashMessage(buf.c_str(), 2, 500, 500);
  
  buf = "Event Time: " + String(telemetryTime);
  m_menuInterface->getLcdInterface()->printToLCD(0, 0, buf.c_str());

  buf = "Implement Id: " + String(implement->getId());
  m_menuInterface->getLcdInterface()->printToLCD(1, 0, buf.c_str());

  m_menuInterface->getLcdInterface()->clearLCD();

  buf = "State: ";
  buf += implement->getState() ? "On" : "Off";
  m_menuInterface->getLcdInterface()->printToLCD(0, 0, buf.c_str());

  buf = "Fuel: " + String(implement->getFuelLevel());
  m_menuInterface->getLcdInterface()->printToLCD(1, 0, buf.c_str());
  
  m_menuInterface->getLcdInterface()->clearLCD();
}

void ImplementManager::scheduleTurnOnEvent(unsigned int implementId)
{
  Event turnOnEvent;
  turnOnEvent.m_time = 0.0;
  turnOnEvent.m_implementId = implementId;
  turnOnEvent.m_eventType = TurnOn;
  m_eventQueue.insert(turnOnEvent);
}

void ImplementManager::scheduleFuelConsumptionEvent(unsigned int implementId, double fuelConsumptionTime)
{
  Event fuelConsumptionEvent;
  fuelConsumptionEvent.m_time = fuelConsumptionTime;
  fuelConsumptionEvent.m_implementId = implementId;
  fuelConsumptionEvent.m_eventType = FuelConsumption;
  m_eventQueue.insert(fuelConsumptionEvent);
}

void ImplementManager::scheduleFuelEmptyEvent(unsigned int implementId, double fuelEmptyTime)
{
  Event fuelEmptyEvent;
  fuelEmptyEvent.m_time = fuelEmptyTime;
  fuelEmptyEvent.m_implementId = implementId;
  fuelEmptyEvent.m_eventType = FuelEmpty;
  m_eventQueue.insert(fuelEmptyEvent);
}

void ImplementManager::scheduleExternalTriggerEvent(unsigned int implementId, bool state, double triggerTime)
{
  Event exTriggerEvent;
  exTriggerEvent.m_time = triggerTime;
  exTriggerEvent.m_implementId = implementId;
  exTriggerEvent.m_eventType = ExternalTrigger;
  exTriggerEvent.m_state = state;
  exTriggerEvent.m_triggerTime = triggerTime;
  m_eventQueue.insert(exTriggerEvent);
}

void ImplementManager::scheduleTelemetryEvent(unsigned int implementId, double telemetryTime)
{
  Event telemetryEvent;
  telemetryEvent.m_time = telemetryTime;
  telemetryEvent.m_implementId = implementId;
  telemetryEvent.m_eventType = Telemetry;
  m_eventQueue.insert(telemetryEvent);
}
