#ifndef SPI_IMPLEMENT_H_
#define SPI_IMPLEMENT_H_

#include <Arduino.h>

#include "implement.h"
#include <SPI.h>

// Define SPI pins
extern const int SCK_PIN;
extern const int MISO_PIN;
extern const int MOSI_PIN;
extern const int SS_PIN;

class SPIImplement : public Implement
{
    int m_ssPin;
public:
    SPIImplement(int ssPin) : m_ssPin(ssPin) {setup();}

    ~SPIImplement(){}

    int getId()const{return m_id;}
    bool getState()const{return m_state;}
    double getFuelLevel()const{return m_fuelLevel;}

    void setId(int id){m_id = id;}
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
