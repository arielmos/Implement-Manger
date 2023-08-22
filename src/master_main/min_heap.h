#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#include <Arduino.h>

enum EventType
{
  TurnOn,
  FuelEmpty,
  ExternalTrigger,
  Telemetry,
  FuelConsumption
};

class Event
{
public:
    double m_time;
    unsigned int m_implementId;
    EventType m_eventType;
    
    bool m_state;

    Event(){};
    Event(double time, unsigned int implementId, EventType eventType);
    Event(double time, unsigned int implementId, EventType eventType, bool state);

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

class MinHeap
{
    Event* heap;
    unsigned int capacity;
    unsigned int size;

    void heapifyUp(unsigned int index);
    void heapifyDown(unsigned int index);
    void resizeHeap(unsigned int newCapacity);
    void swap(Event& a, Event& b);
    
public:
    MinHeap(unsigned int initialCapacity);
    ~MinHeap();
    
    unsigned int getSize()const{return size;}
    bool isEmpty()const{return size == 0;} 
    void insert(const Event& event);
    void pop();
    Event top()const;
    void printHeap();
};
#endif /* MIN_HEAP_H_ */
