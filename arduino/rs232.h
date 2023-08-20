#ifndef HEADERS_RS232_H_
#define HEADERS_RS232_H_

#include "implement.h"

class RS232Implement : public Implement {
public:
    ~RS232Implement(){};

    int getId()const{return m_id;}

    int getState()const{return m_state;}

    double getFuelLevel()const{return m_fuelLevel;}

    void setId(int id){m_id = id;}

    void setState(int state){m_state = state;}

    void setFuelLevel(double level){m_fuelLevel = level;}



    // Telemetry methods
//    void sendTelemetry(const TelemetryData& data)
//    {
//        // Implement RS232 telemetry sending logic
//    }
//
//    TelemetryData receiveTelemetry()
//    {
//        // Implement RS232 telemetry receiving logic
//        TelemetryData data;
//        // Populate data by reading from RS232
//        return data;
//    }

    // Other functionalities specific to RS232
    void calibrateSensor()
    {
        // Implement RS232 sensor calibration logic
    }
};



#endif /* HEADERS_RS232_H_ */
