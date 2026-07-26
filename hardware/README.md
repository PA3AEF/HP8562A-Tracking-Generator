# Hardware — TG Project

This directory contains all hardware designs for the modular Tracking Generator (TG).  
Each RF module is fully self‑contained with its own schematic, PCB if applicable, and data on on read-made building-blocks.

The hardware is organized into four primary modules:

- **Baseband Module (0–2.9 GHz)**
- **6 cm Module (4.4–6.4 GHz)**
- **3 cm Module (8.5–11.5 GHz)**
- **LO Module (Isolation and distribution of 1st LO from SA)**

All PCBs are designed in KiCad and stored in separate subdirectories.

---

## Directory Structure

Each module directory contains:

- **`schematic.pdf`** — complete schematic  
- **`pcb/`** — KiCad PCB files, 3D views, fabrication output  
- **`bom.csv`** — Bill of Materials  
- **`readme.md`** — module‑specific documentation (gain budget, design notes, test plan)

---

## Hardware Module Overview

### **Baseband Module (0–2.9 GHz)**
- IF chain from the HMC219 downconverter
- PLL at 3.9107 GHz  
- 3 GHz low‑pass filter  
- Pads, IF amplifier, SMA output  

### **6 cm Module (4.4–6.4 GHz)**
- HMC220 mixer  
- IF and RF amplification  
- Band‑pass filtering for 4–8 GHz  
- Purpose: upconversion for the 6 cm tracking generator band

### **3 cm Module (9.5–11.5 GHz)**
- HMC220 mixer 
- PLL at 310.7 MHz
- Band-pass filter at 310 MHz 
- High‑frequency RF amplifier (9–12 GHz)  
- Band‑pass filtering for 8–12 GHz  
- Purpose: upconversion for the 3 cm tracking generator band

### **Control Module**
- Raspberry Pi microcontroller
- Control of all circuitry, indicators, etc.
- Power provision for each band module (5-12V selectable) 
- Prper startup-shutdown sequence for band switching
- 10 MHz reference input buffering and distribution (SMA)
- SPI control for PLLs 

### **LO Module**
- Isolation of 1st LO output of analyser
- Braodband amplification of 1st LO output
- Distribution of 1st LO to band modules 

---

## Design Principles

- **Modular:** each RF module is electrically and mechanically independent  
- **SMA‑based:** all interconnects use SMA cables for clean, predictable RF paths  
- **Reproducible:** BOMs, schematics, and PCB files are fully documented  
- **RF‑optimized:** short signal paths, solid grounding, controlled impedance  
- **Measurable:** each module includes clear test points and a documented gain budget

---


