
# Wake-on-LAN C++ Project

## Overview

This C++ project demonstrates the usage of the Wake-on-LAN (WoL) protocol to remotely power on a computer over the network. It sends a magic packet to the target PC's MAC address, triggering the Wake-on-LAN functionality.

## Prerequisites

- Windows operating system (the example uses Winsock for socket programming)
- C++ compiler (e.g., Visual Studio, MinGW)
- Administrative privileges to send Wake-on-LAN packets

## Usage

1. Clone or download the project to your local machine.

    ```bash
    git clone https://github.com/KayleBrown/WakeOnLan.git
    ```

2. Open the project in your preferred C++ development environment.

3. Modify the `wakeOnLAN` function in the `wakeOnLAN.cpp` file to set the target PC's MAC address:

    ```cpp
    // Replace "00:11:22:33:44:55" with the target PC's MAC address
    wakeOnLAN("00:11:22:33:44:55");
    ```

4. Build and run the project. Ensure that the program is executed with administrative privileges.

## Important Note

Before using this code, make sure the BIOS/UEFI settings of the target PC allow Wake-on-LAN. Additionally, the network should be configured to permit Wake-on-LAN packets.
