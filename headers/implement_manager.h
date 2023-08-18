/*
 * implement_manager.h
 *
 *  Created on: 16 Aug 2023
 *      Author: mozes
 */

#ifndef HEADERS_IMPLEMENT_MANAGER_H_
#define HEADERS_IMPLEMENT_MANAGER_H_

// implement_manager.h
#include <vector>
#include "implement.h"

class ImplementManager {
public:
    void addImplement(Implement* implement)
    {
        implements.push_back(implement);
    }

    void triggerCommand(int implementIndex, bool turnOn)
    {
        if (implementIndex >= 0 && implementIndex < implements.size())
        {
            if (turnOn)
            {
                implements[implementIndex]->turnOn();
            }
            else
            {
                implements[implementIndex]->turnOff();
            }
        }
    }

    // Similar methods for telemetry and fuel level handling
private:
    std::vector<Implement*> implements;
};



#endif /* HEADERS_IMPLEMENT_MANAGER_H_ */
