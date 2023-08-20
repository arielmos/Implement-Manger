#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#include <Arduino.h>

enum EventType
{
  TurnOn,
  TurnOff,
  FuelEmpty,
  ExternalTrigger,
  Telemetry,
  FuelConsumption
};

class Event {
public:
    double m_time;
    int m_implementId;
    EventType m_eventType;
    
    bool m_state;
    double m_triggerTime;

    Event(){};
    Event(double time, int implementId, EventType eventType);
    Event(double time, int implementId, EventType eventType, bool state, double triggerTime);

    bool operator<(const Event& other) const
    {
        if (m_time != other.m_time)
        {
            return m_time < other.m_time;
        }
        else
        {
          if(m_implementId != other.m_implementId)
          {
            return m_implementId < other.m_implementId;
          }
          else
          {
            return m_eventType < other.m_eventType;
          }
        }
    }
};

class MinHeap {
    Event* heap;
    int capacity;
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resizeHeap(int newCapacity);
    void swap(Event& a, Event& b);
    
public:
    MinHeap(int initialCapacity);
    ~MinHeap();
    
    int getSize()const{return size;}
    bool isEmpty()const{return size == 0;} 
    void insert(const Event& event);
    void pop();
    Event top()const;
    void printHeap();
};
#endif /* MIN_HEAP_H_ */
