# Implement-Manger - Embedded Software Engineer Assignment


![ezgif-2-f433b00266](https://github.com/arielmos/Implement-Manger/assets/54889635/acbafe92-edf6-47b2-9591-fdfee437e457)

# Tractor Implement Management System

Welcome to the Tractor Implement Management System repository! This project demonstrates an embedded software solution for managing tractor implements through an event-driven simulation. The system is built using two Arduino microcontrollers connected using the SPI protocol, and each Arduino is equipped with an LCD screen for visual feedback.

## Overview

In this project, we've developed a software module that effectively manages multiple tractor implements, allowing them to be turned on or off and providing telemetry data such as implement status and fuel level. The software is designed to be highly modular and event-driven, ensuring efficient communication between the different components.

To monitor the communication and events between the Arduinos and the Implement Manager, use the serial monitor available on the host computer for both Arduino boards.

## Features

- **Dual Arduino Setup:** Two Arduino microcontrollers are connected using the SPI protocol. Each Arduino is responsible for simulating the behavior of an individual tractor implement.

- **LCD Screens:** Each Arduino is connected to an LCD screen, providing real-time visual feedback about the status of the implements and their telemetry data.

- **Event-Driven Simulation:** The software is designed in an event-driven manner, allowing the implement manager to react to external triggers and internal events, such as turning an implement on or off, receiving telemetry data, and managing fuel levels.

- **Serial Monitor:** The Arduino master's serial monitor interface provides 2 functionalities:
  - View the real-time status of all connected implements, including whether they are on or off.
  - Toggle the state of implements on/off using external commands sent via the serial monitor.

- **SPI Communication:** The communication between the two Arduinos is achieved using the Serial Peripheral Interface (SPI) protocol, which enables efficient data exchange between the devices.

## Implementation

The core of the project is the Implement Manager, which oversees the interaction between the two Arduino microcontrollers and the LCD screens. Each Arduino simulates the behavior of a tractor implement and communicates with the Implement Manager through the SPI protocol. The Implement Manager processes commands, updates telemetry data, and ensures the proper functioning of the implements.

## Getting Started

To get started with the project, follow these steps:

1. Clone this repository to your local machine.
2. Connect two Arduino boards to your computer.
3. Connect the LCD screens to the Arduinos according to the hardware schematic.
4. Upload the appropriate code to each Arduino from the source files and open serial monitors.
5. Configure simulation parameters to your choice in [Implement Manager Header File](/src/master_main/implement_manager.h).
6. Run the simulation and observe the LCD screens & serial monitors for real-time feedback on implement status and events. 

For detailed instructions on setting up the hardware and running the software, please refer to the hardware schematic. 


## Software Schematic
![schematic-Classes](https://github.com/arielmos/Implement-Manger/assets/54889635/1acd5f33-264a-4ad6-b04f-79c6757cfc60)

![schematic-Flow](https://github.com/arielmos/Implement-Manger/assets/54889635/90cc6f78-f7ca-4f7e-89d7-7ed733a24a21)

## Hardware Schematic
![ImplementManger_hardware_schematic](https://github.com/arielmos/Implement-Manger/assets/54889635/f1f94591-a5c1-42e9-a959-47b2eddb8673)
