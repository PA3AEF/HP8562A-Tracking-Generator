# Firmware Architecture HP8562A Tracking Generator

This document describes the modular firmware architecture used in the **HP8562A Tracking Generator** project.  
It complements the system‑level design documents in `/docs/architecture` and focuses on the internal structure, sequencing, and logic of the firmware modules.

---

## 1. Overview

The firmware controls the TG’s mixed‑PLL synthesizer system (MAX2870 + ADF4351), band‑switching logic, and RF routing.  
It is designed for clarity, reproducibility, and modularity, following a clean separation between hardware abstraction and signal‑chain logic.

### Key design goals
- Deterministic band‑switching sequence  
- Unified PLL programming interface  
- Operator‑friendly feedback and debug output  
- Safe RF transitions (no hot‑switching)  
- Extensible for future bands or PLL types  

---

## 2. Directory Structure

/firmware  
  src/  
   • Tracking_Generator.ino 
   • pins.h  
   • bands.h / bands.cpp  
   • pll_max2870.h / pll_max2870.cpp  
   • pll_adf4351.h / pll_adf4351.cpp    
   • pll_control.h / pll_control.cpp  
   • pe42540.h / pe42540.cpp
   • ramp.h / ramp.cpp  
   • rotary.h / rotary.cpp  
   docs/  
   • firmware_architecture.md  

Each module has a single responsibility and can be tested independently.

---

## 3. Module Responsibilities

**pins.h** - Defines all GPIO assignments  
**bands.cpp** - Implements band table, state machine, and switching logic  
**pll_max2870.cpp / pll_adf4351.cpp** - Compute register sets for each PLL type  
**pll_control.cpp** - Holds static default register sets per band  
**pe42540.cpp** - Controls LO routing switch
**ramp.cpp** - Converts ramp ADC value to LO frequency  
**rotary.cpp** - Reads Gray‑code band selector  
**Tracking_Generator.ino** - Initializes modules and runs the control loop  

---

## 4. Band‑Switching Sequence

The firmware follows an eight‑step, RF‑safe switching sequence:

1. Disable old gain block (`PIN RFEN_xx LOW`)  
2. Disable old PLL (`PIN CE_xx LOW`)  
3. Switch LO path (PE42540)  
4. Enable new PLL (`PIN CE_xx HIGH`)  
5. Program PLL registers  
6. Wait for lock (`PIN LD_xx HIGH`)  
7. Enable new gain block (`PIN RFEN_xx HIGH`)  
8. New band active  

### Sequence Diagram  

![Band switching sequence](./band-switching-sequence.png)

### Timing Diagram  

![Band switching timing](./band-switching-timing.png)

These diagrams illustrate the relative timing of RF_EN, PLL_CE, LO Switch, and PLL Lock Detect signals.

---

## 5. Safety and Timing Considerations

- RF_EN is always turned off before any LO or PLL transition  
- PLL_CE is toggled only when RF_EN is low  
- PE42540 switching occurs with no RF present  
- PLL lock time is verified before enabling RF output  
- Typical delays:  
  • CE‑to‑SPI start: 500 µs  
  • SPI burst: ~100 µs  
  • Lock wait: 5–10 ms (band‑dependent)  

---


## 6. Build and Deployment

- Platform: Raspberry Pi Pico (RP2040)  
- Toolchain: Arduino RP2040 Core  
- SPI speed: 1 MHz (safe for MAX2870/ADF4351)  
- Serial debug: 115200 baud  
- Upload via USB using Arduino IDE or CLI  

---

## 7. References

- MAX2870 Datasheet  
- ADF4351 Datasheet  
- PE42540 Datasheet  

---

