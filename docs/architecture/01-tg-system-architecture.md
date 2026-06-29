# Tracking Generator System Architecture  
**Modules:** LO Distribution, Base‑Band, 3 cm, 6 cm (future), 12 mm (future)  
**Coherence Sources:** Analyzer 1st LO, Analyzer 10 MHz reference  
**Architecture:** Distributed mixer‑based TG with per‑band modules  
**Control:** Central MCU (Raspberry Pi Pico)

---

## Overview

The Tracking Generator (TG) system is a modular, analyzer‑synchronous signal source covering:

- **Base‑Band:** 0–2.9 GHz  
- **6 cm:** 4.4-6.4 GHz 
- **3 cm:** 9.5–11.5 GHz  
- **12 mm:** 23-25 Ghz (future)  

All TG modules derive their timing and frequency coherence from the **spectrum analyzer’s internal LO system**, ensuring that the TG output always tracks the analyzer sweep.

Two analyzer signals form the foundation:

- **1st LO** (swept, 3.9–6.8 GHz)  
- **10 MHz reference** (system clock)

The TG system uses these to generate all required LOs for each band.

---

## System‑level signal flow

The TG system is composed of six boards:

1. **MCU (Raspberry Pi Pico)**  
2. **RF SA‑LO Distribution Module**  
3. **Base‑Band TG Module**  
4. **6 cm TG Module**  
5. **3 cm TG Module**  
6. **12 mm TG Module** (future)

The analyzer’s 1st LO enters the system through the **LO Distribution Module**, which conditions and splits it to all TG modules.  
Each TG module then generates its own internal LO(s) and performs mixing to reconstruct the analyzer RF at its target band.

---

## LO architecture summary

### Analyzer 1st LO  
- 3.9–6.8 GHz  
- Sweep‑synchronous  
- Distributed to all TG modules at +16 dBm

### Analyzer 10 MHz reference  
- Shared reference for all PLLs  
- Ensures long‑term coherence

### Base‑Band module  
- Internal IF LO: MAX2870 at 3.9107 GHz (fixed)  
- Mixer: HMC219  
- Output: 0–2.9 GHz

### 6 cm module  
- Internal IF LO: ADF4351 at 310.7 MHz (fixed)  
- Mixer: HMC219
- Output: 4.4-6.4 GHz

### 3 cm module  
- High‑frequency LO: Doubled analyzer LO (8.94–10.28 GHz)  
- Internal IF LO: ADF4351 at 310.7 MHz (fixed)  
- Mixer: HMC220  
- Output: 9.5–11.5 GHz

### 12 mm module (future)  
- Will require higher‑order multiplication  
- Output expected in 23-25 GHz region

---

## Block diagram

![TG system architecture](/docs/architecture/images/tg-system-architecture.png)

---

## Power distribution & LO levels

| Path | Level | Notes |
|------|------:|-------|
| Analyzer 1st LO → Distribution | +16.5 dBm | Raw analyzer output |
| Distribution → TG modules | +16 dBm | After isolator, amp, splitter, pad |
| TG module LO input | +13 dBm | After on‑module pad/filter |
| TG mixer LO input | +13 dBm | After LO chain |
| Output | 0 dBm | After filters, amp, pad|

All levels are chosen to meet mixer LO drive requirements and maintain isolation.

---

## Control architecture

### MCU responsibilities  
- Program MAX2870 (Base‑Band)  
- Program ADF4351 (6 cm and 3 cm)  
- Compute sweep‑dependent IF if needed 
- Manage LO enable/mute  
- Monitor PLL lock‑detect  
- Handle band selection  

### Shared resources  
- SPI bus shared across all PLLs  
- Dedicated chip‑select per module  
- 10 MHz reference distributed to all PLLs  
- Optional GPIO for LO mute and module enable

---

## Calibration architecture

Each module supports:

- Output level trimming via pads  
- LO drive trimming  
- Mixer conversion‑loss compensation  


System‑level calibration ensures:

- Consistent output level across bands  
- Flatness across each module’s span  
- Coherent phase relationship with analyzer LO

---

## Mechanical / layout considerations

- Analyser LO input at front panel (Cabinet below SA)
- LO Distribution module placed closest to analyzer LO input  
- TG modules arranged to minimize LO crosstalk  
- Shielding around mixers, doublers, and LO amplifiers  
- Consistent grounding across all modules  
- SMA connectors clearly labeled by band  

---

## Future expansion

The architecture is designed to scale to:

- Additional TG bands (e.g. modular RF front-ends with MCU band-descriptor table for LO range, step size, level, etc.) 
- Higher‑order multipliers (e.g. multiplier blocks as seperate modules with additional filters while keeping the PLLs at a comfortable range)
- Optional LO monitoring ports (e.g. directional couplers on LO lines for calibration hooks in the MCU) 
- Optional TG output leveling loops (e.g. per-band detector with digital step attenuators) 
- Optional digital predistortion for flatness correction

All highly ambitious but no roadblocks in the architecture for possible future developmenst . 

---