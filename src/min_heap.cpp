#include "min_heap.h"

Event::Event(double time, int implementId, EventType eventType)
        : m_time(time), m_implementId(implementId), m_eventType(eventType){}

Event::Event(double time, int implementId, EventType eventType, bool state, double triggerTime)
        : m_time(time), m_implementId(implementId), m_eventType(eventType), m_state(state), m_triggerTime(triggerTime){}

void MinHeap::heapifyUp(int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (heap[index] < heap[parentIndex])
        {
            swap(heap[parentIndex], heap[index]);
            index = parentIndex;
        } 
        else
        {
            break;
        }
    }
}

void MinHeap::heapifyDown(int index)
{
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < size && heap[leftChild] < heap[smallest])
    {
        smallest = leftChild;
    }
    if (rightChild < size && heap[rightChild] < heap[smallest])
    {
        smallest = rightChild;
    }

    if (smallest != index)
    {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

void MinHeap::resizeHeap(int newCapacity)
{
    Event* newHeap = new Event[newCapacity];
    for (int i = 0; i < size; ++i)
    {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

void MinHeap::swap(Event& a, Event& b)
{
    Event temp = a;
    a = b;
    b = temp;
}

MinHeap::MinHeap(int initialCapacity) : capacity(initialCapacity), size(0)
{
    heap = new Event[capacity];
}

MinHeap::~MinHeap()
{
    delete[] heap;
}

void MinHeap::insert(const Event& event)
{
    if (size == capacity)
    {
        // Double the capacity and resize the heap
        resizeHeap(capacity * 2);
    }
    heap[size] = event;
    heapifyUp(size);
    size++;
}

void MinHeap::pop()
{
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);

    // Shrink the heap if size becomes too small
    if (size <= capacity / 4 && capacity > 4)
    {
        resizeHeap(capacity / 2);
    }
}

Event MinHeap::top()const
{
  return !isEmpty() ? heap[0] : Event();
}

void MinHeap::printHeap()
{
    for (int i = 0; i < size; ++i)
    {
        Serial.print("currentEvent.m_time = ");
        Serial.print(heap[i].m_time);
        Serial.print(", currentEvent.m_implementId = ");
        Serial.println(heap[i].m_implementId);
    }
}
