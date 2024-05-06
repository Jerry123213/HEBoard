# HEBoard
## OUTDATED SEE BRANCH ver4

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

### Next Step: Implement Adjustable Actuation Force Hardware
There are two options for adjustable actuation force. The original idea was to wind an electromagnet larger than the area of both switches such that the switches rest inside the solenoid. The magnetic field would be used to repel the magnet inside the switch, and adjusting the PWM-cycle of the electromagnet would alter the strength of the field. 

* Issues
  * Due to size, would likely require external power source (not from MCU or USB), which increases footprint of device
  * A coil's volume is constant, therefore, regardless of the coil shape, footprint would still be large
  * Possible heat dissipation issues, especially bad since HEBoard is a HID
  * Not scalable, or incredibly hard to scale
  * Possible EMI? 

Current idea is to make use of PCB coils. Rather than winding one large electromagnet, each switch can have its own PCB coil directly underneath, allowing for scalability. Due to proximity to switch, the size can be reduced, and won't need to be especially strong (for keyboards a 20g difference in actuation force is large).

* Issues
  * There is very little documentation on PCB coils compared to conventional electromagnets
  * Power is still an issue, but this requires testing (no documentation on the magnet inside Lekker switch, which makes calculations difficult)
  * Possibly expensive depending on coil required, especially if a stronger magnetic field is needed (stronger magnetic field requires more PCB layers)
 
### Implemented Hardware
Third revision of PCB is complete. Updated to a two-layer PCB with ground pours on both layers. Updated from micro-USB to USB-C 2.0. Better trace routing for better signal integrity across differential pairs (D+ and D-) as well as analog output of switches. Via switching across D+ and D- to ensure simple ground return. 

#### Technical Specs: 
* Wooting Lekker Switch 
  * Normal Bottom Out Force: 45g or 65g depending on model
  * 4mm of Travel
* SS39E Linear Hall-Effect Sensor
* USB-C 2.0 Port
* ATMega32u4 Microcontroller Flashed with Arduino Pro Micro Firmware

### Implemented Firmware
* Firmware for "Rapid Trigger" is done
  * Implemented by reading output of SS49E and checking for lowest or highest voltage in a "cycle"
    * When the lowest/highest voltage is not being updated, indicates a change in direction, check if change in direction is greater than user-set threshold. If so, the keyboard releases/actuates.
* Firmware for adjustable acutation point is done
  * Partitioned delta between resting voltage and bottom-out voltage into 40 parts, resulting in a distance of 0.1mm per part. User-set acutation point is defined as a multiple of said parts
* Firmware for calibration is done
  * To find resting/bottom out voltage, calibration mode asks user to fully depress switch for given time, and takes the average voltage reading, storing it into memory

### Future Improvements (Unconfirmed)
* Low-Level or QMK firmware
* Adjustable acutation force (both firmware and hardware required)
* Front-end application to make user-experience smoother
* May switch to USB 3.0 for higher current draw
