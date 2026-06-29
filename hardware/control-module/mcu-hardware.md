# Control Module — MCU Hardware (Raspberry Pi Pico 2)

The MCU Module hosts the **Raspberry Pi Pico 2**, providing system control, SPI fan‑out, power‑good monitoring, and hardware‑level interfacing to all RF Modules. It exposes USB for host communication and SWD for programming/debug.  
Detailed schematics and electrical notes are in:  
- **`docs/mcu-hardware.md`**  
- **`docs/10MHz_reference.md`** (for the reference buffer subsystem)

---

## Purpose

- Provide a stable hardware platform for system control  
- Interface with RF Modules via **SPI**, **GPIO**, and fault/status lines  
- Offer **USB** as the sole host interface  
- Provide **SWD** for programming and debugging  
- Implement power‑good sensing and system‑level monitoring  

---

## Block Diagram

Power In → Protection → Regulators → **Pico 2**  
Pico 2 → SPI Header → RF Modules  
Pico 2 → USB → Host  
Pico 2 → SWD → Programming / Debug  
Pico 2 → Status LEDs

---

## Hardware Interfaces

### SPI Bus
- Pico 2 as SPI master  
- MOSI, MISO, SCLK, CS lines routed to a 6‑pin header  
- Series resistors for signal integrity  
- Optional per‑module chip‑select expansion

### USB (Host Interface)
- USB‑C or Micro‑USB connector (depending on PCB revision)  
- ESD protection on D+/D−  
- USB provides data only; power comes from main DC input  

### SWD (Programming / Debug)
- 3‑pin or 4‑pin SWD header (SWDIO, SWCLK, GND, optional 3V3)  
- Reset pin accessible via test pad  
- Suitable for production programming and field debugging  

### Power
- External DC input with reverse‑polarity protection  
- Local regulators for 5 V → 3.3 V  
- Power‑good signal routed to Pico 2  
- Decoupling around MCU supply pins  

### Status & Fault Indicators
- Power LED  
- Reference‑present LED (from reference buffer module)  
- Fault LED per module (basically Lock-Detect) driven by Pico 2  

---

## Design Notes (Hardware)

- **Noise isolation:**  
  Pico 2 digital switching kept physically separated from the 10 MHz reference path; ground stitching and ferrites reduce coupling.

- **Signal integrity:**  
  SPI traces length‑matched; series damping resistors on high‑speed lines.

- **Protection:**  
  TVS diodes on USB, ESD diodes on GPIO headers, reverse‑polarity MOSFET on power input.

- **Mechanical:**  
  USB connector and SWD header placed at board edge for easy access.


---

## Connector Summary

- **SPI Header:** MOSI, MISO, SCLK, CS, GND, Vcc  
- **USB:** USB‑C or Micro‑USB (data only)  
- **SWD:** 3‑ or 4‑pin programming header  
- **Power Input:** Screw terminal or pin-header  
- **Status LEDs:** Power, Reference, Fault (No Lock)  

---
