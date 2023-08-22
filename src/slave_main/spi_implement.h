#ifndef SPI_IMPLEMENT_H_
#define SPI_IMPLEMENT_H_

#include <Arduino.h>

#include "implement.h"
#include <SPI.h>

#include "lcd.h"


// Define SPI pins
extern const unsigned int SCK_PIN;
extern const unsigned int MISO_PIN;
extern const unsigned int MOSI_PIN;
extern const unsigned int SS_PIN;

extern char buff [50];
extern volatile byte indx;
extern volatile boolean process;
extern myLcd* lcdInstance;

class SPIImplement : public Implement
{
    unsigned int m_ssPin;
public:
    SPIImplement(unsigned int ssPin) : m_ssPin(ssPin)
    {  
      setup();
    }

    ~SPIImplement(){}

    unsigned int getId()const{return m_id;}
    bool getState()const{return m_state;}
    double getFuelLevel()const{return m_fuelLevel;}
  
    void setId(unsigned int id){m_id = id;}
    void setState(bool state){m_state = state;}
    void setFuelLevel(double level){m_fuelLevel = level;}

    void setup();
    void handlePrint();

    // Other functionalities specific to SPI
    void calibrateSensor()
    {
        // Implement SPI sensor calibration logic
    }
};


#endif /* SPI_IMPLEMENT_H_ */
