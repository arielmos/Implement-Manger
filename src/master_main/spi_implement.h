#ifndef SPI_IMPLEMENT_H_
#define SPI_IMPLEMENT_H_

#include <Arduino.h>

#include "implement.h"
#include <SPI.h>

// Define SPI pins
extern const unsigned int SCK_PIN;
extern const unsigned int MISO_PIN;
extern const unsigned int MOSI_PIN;
extern const unsigned int SS_PIN;

class SPIImplement : public Implement
{
    unsigned int m_ssPin;
public:
    SPIImplement(unsigned int ssPin) : m_ssPin(ssPin) {setup();}

    ~SPIImplement(){}

    unsigned int getId()const{return m_id;}
    bool getState()const{return m_state;}
    double getFuelLevel()const{return m_fuelLevel;}

    void setId(unsigned id){m_id = id;}
    void setState(bool state);
    void setFuelLevel(double level);

    void setup();
    void calibrateSensor();

    // Telemetry methods
    byte send(byte data);
    String sendString(const String &data);
    byte receive();
};


#endif /* SPI_IMPLEMENT_H_ */
