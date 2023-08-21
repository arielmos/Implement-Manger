#ifndef RS232_IMPLEMENT_H_
#define RS232_IMPLEMENT_H_

#include <Arduino.h>

#include "implement.h"

class RS232Implement : public Implement
{
public:
    ~RS232Implement(){};

    int getId()const{return m_id;}
    bool getState()const{return m_state;}
    double getFuelLevel()const{return m_fuelLevel;}

    void setId(int id){m_id = id;}
    void setState(bool state){m_state = state;}
    void setFuelLevel(double level){m_fuelLevel = level;}

    void setup();
    void calibrateSensor();

    // Telemetry methods
    byte send(byte data);
    String sendString(const String &data);
    byte receive();
};



#endif /* RS232_IMPLEMENT_H_ */
