//============================================================================
// Name        : main.cpp
// Author      : Ariel
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "implement_manager.h"
#include "rs232.h"  // Include other protocol headers as needed

int main() {
    RS232Implement rs232Implement;
    // Create other implement instances for different protocols

    ImplementManager implementManager;
    implementManager.addImplement(&rs232Implement);
    // Add other implements to the manager

    int selectedImplementIndex = 0;
    bool turnOn = true;  // Or false to turn off
    implementManager.triggerCommand(selectedImplementIndex, turnOn);

    // Add code for telemetry and fuel level handling

    return 0;
}
