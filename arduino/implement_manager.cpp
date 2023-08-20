#include "implement_manager.h"
#include "rs232.h"

void ImplementManager::addImplement(Implement* implement)
{
    if(m_implementCount < MAX_IMPLEMENT_COUNT)
    {
      implement->setId(m_implementCount);
      m_implements[m_implementCount++] = implement;
    }
    else 
    {
        // Handle case where the array is full
    }
}

void ImplementManager::setup()
{
  m_menuInterface->getLcdInterface()->lcdSetup();
  Serial.begin(9600);
}

const double simulationTime = 10;
const double timeStep = 1e-2;
const double fuelConsumptionRate = 1;
const double someTelemetryInterval = 5;

void ImplementManager::initializeSimulation()
{
  Serial.println("======================================");
  Serial.println("Hello BlueWhite! Initialize Simulation");
  Serial.println("======================================");  

  m_menuInterface->getLcdInterface()->printToLCD(0, 0, "Hello BlueWhite!");
  m_menuInterface->getLcdInterface()->printToLCD(1, 0, "Init Simulation");
  
  delay(lcdDelay);
  m_menuInterface->getLcdInterface()->clearLCD();
  delay(lcdDelay);


  // Initialize implements
  Implement* rs232Implements = new RS232Implement[3];

  
  // Create other implement instances for different protocols

  for (int i = 0; i < 3; i++)
  {
    addImplement(&rs232Implements[i]);
  }
 
  // Add more implements as needed
  
//  // Add initial turn-on events for each implement
  for (int i = 0; i < m_implementCount; i++)
  {
    scheduleTurnOnEvent(m_implements[i]->getId());
  }
}

void ImplementManager::runSimulation()
{
  double currentTime = getCurrentTime();
  
  if(currentTime < simulationTime)
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

        case TurnOff:
        case FuelEmpty:
          implement->setState(false);
          Serial.println("ImplementManager::runSimulation: TurnOff");
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

    for (int i = 0; i < m_implementCount; i++)
    {
      if (m_implements[i]->getState())
      {
        scheduleFuelConsumptionEvent(m_implements[i]->getId(), getCurrentTime());
      }
    }

    // Update simulation time
    setCurrentTime(currentTime + timeStep);
    delay(50);
  }
}

void ImplementManager::processFuelConsumption(Implement* implement, Event& currentEvent)
{
    double timeDelta = getCurrentTime() - currentEvent.m_time;
    implement->setFuelLevel(implement->getFuelLevel() - fuelConsumptionRate * timeDelta);
    
    if (implement->getFuelLevel() <= 0.0)
    {
      implement->setFuelLevel(0.0);
      scheduleFuelEmptyEvent(currentEvent.m_implementId, currentEvent.m_time);
    }
}

void ImplementManager::processTurnOn(Implement* implement, Event& currentEvent)
{
    implement->setState(true);
    implement->setFuelLevel(100.0);
    Serial.println("ImplementManager::runSimulation: TurnOn");
    processTelemetry(implement, currentEvent.m_time);
}

void ImplementManager::processExternalTrigger(Implement* implement, Event& currentEvent)
{
    implement->setState(currentEvent.m_state);

    if(currentEvent.m_state)
    {
      Serial.println("ImplementManager::runSimulation: TurnOn");
    }
    else
    {
      Serial.println("ImplementManager::runSimulation: TurnOff");
    }
    processTelemetry(implement, currentEvent.m_time);
}

void ImplementManager::processTelemetry(Implement* implement, double telemetryTime)
{
  String buf = "ImplementManager::processTelemetry: Time: " + String(telemetryTime) +
                " Implement Id: " + String(implement->getId()) + " State: " + String(implement->getState()) +
                " Fuel Level: " + String(implement->getFuelLevel());
  Serial.println(buf);
  
  buf = "Time: " + String(telemetryTime);
  m_menuInterface->getLcdInterface()->printToLCD(0, 0, buf.c_str());
  
  buf = "Implement Id: " + String(implement->getId());
  m_menuInterface->getLcdInterface()->printToLCD(1, 0, buf.c_str());
  
  delay(lcdDelay);
  
  buf = "State Id: " + String(implement->getState());
  m_menuInterface->getLcdInterface()->printToLCD(0, 0, buf.c_str());
  
  buf = "Fuel Level: " + String(implement->getFuelLevel());
  m_menuInterface->getLcdInterface()->printToLCD(1, 0, buf.c_str());
  
  delay(lcdDelay);
  
  m_menuInterface->getLcdInterface()->clearLCD();
}

void ImplementManager::scheduleTurnOnEvent(int implementId)
{
  Event turnOnEvent;
  turnOnEvent.m_time = 0.0;
  turnOnEvent.m_implementId = implementId;
  turnOnEvent.m_eventType = TurnOn;
  m_eventQueue.insert(turnOnEvent);
}

void ImplementManager::scheduleFuelConsumptionEvent(int implementId, double fuelConsumptionTime)
{
  Event fuelConsumptionEvent;
  fuelConsumptionEvent.m_time = fuelConsumptionTime;
  fuelConsumptionEvent.m_implementId = implementId;
  fuelConsumptionEvent.m_eventType = FuelConsumption;
  m_eventQueue.insert(fuelConsumptionEvent);
}

void ImplementManager::scheduleFuelEmptyEvent(int implementId, double fuelEmptyTime)
{
  Event fuelEmptyEvent;
  fuelEmptyEvent.m_time = fuelEmptyTime;
  fuelEmptyEvent.m_implementId = implementId;
  fuelEmptyEvent.m_eventType = FuelEmpty;
  m_eventQueue.insert(fuelEmptyEvent);
}

void ImplementManager::scheduleExternalTriggerEvent(int implementId, bool state, double triggerTime)
{
  Event exTriggerEvent;
  exTriggerEvent.m_time = triggerTime;
  exTriggerEvent.m_implementId = implementId;
  exTriggerEvent.m_eventType = ExternalTrigger;
  exTriggerEvent.m_state = state;
  exTriggerEvent.m_triggerTime = triggerTime;
  m_eventQueue.insert(exTriggerEvent);
}

void ImplementManager::scheduleTelemetryEvent(int implementId, double telemetryTime)
{
  Event telemetryEvent;
  telemetryEvent.m_time = telemetryTime;
  telemetryEvent.m_implementId = implementId;
  telemetryEvent.m_eventType = Telemetry;
  m_eventQueue.insert(telemetryEvent);
}
