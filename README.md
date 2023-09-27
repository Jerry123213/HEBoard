# HEBoard
The HEBoard (Hall-Effect Board) is an analog hall-effect Keypad capable of adjustable actuation point, actuation upon release, and adjustable actuation force (WIP).

## Table Of Contents:
1. Features
2. Implemented Hardware
3. Implemented Firmware

### Features
* Able to detect switch depression with resolution of 0.1mm (Testing Lower Values WIP)
* Adjustable actuation point
* "Rapid Trigger" with adjustable press and release thresholds down to 0.1mm
* Adjustable Actuation Force (WIP)

### Implemented Hardware
First and second revisions of PCB have been made. Third one should be the final one. Planning to transition to 4-layer PCB with a ground and power plane for cleaner routing and better signal integrity. Decoupling capacitors used on ss49E to smooth out resting voltage.

#### Next Step: Implement Adjustable Actuation Force Hardware


#### Technical Specs: 
* Wooting Lekker Switch 
  * Normal Bottom Out Force: 45g or 65g depending on model
  * 4mm of Travel
* SS49E Linear Hall-Effect Sensor
* USB-C Port
* ATMega32u4 Microcontroller Flashed with Arduino Pro Micro Firmware

### Implemented Firmware
* Firmware for "Rapid Trigger" is done
  * Implemented by reading output of SS49E and checking for lowest or highest voltage in a "cycle"
    * When the lowest/highest voltage is not being updated, indicates a change in direction, check if change in direction is greater than user-set threshold. If so, the keyboard releases/actuates.
* Firmware for adjustable acutation point is done
  * Partitioned delta between resting voltage and bottom-out voltage into 40 parts, resulting in a distance of 0.1mm per part. User-set acutation point is defined as a multiple of said parts
* Firmware for calibration is done
  * To find resting/bottom out voltage, calibration mode asks user to fully depress switch for given time, and takes the average voltage reading, storing it into memory  
  
