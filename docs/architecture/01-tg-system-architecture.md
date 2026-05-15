# Tracking Generator System Architecture  
**Modules:** LO Distribution, Base‑Band, 3 cm, 6 cm (future), 15 mm (future)  
**Coherence Sources:** Analyzer 1st LO, Analyzer 10 MHz reference  
**Architecture:** Distributed mixer‑based TG with per‑band modules  
**Control:** Central MCU (Raspberry Pi Pico)

---

## Overview

The Tracking Generator (TG) system is a modular, analyzer‑synchronous signal source covering:

- **Base‑Band:** 0–2.9 GHz  
- **3 cm:** 9.5–11.5 GHz  
- **6 cm:** future  
- **15 mm:** future  

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
4. **6 cm TG Module** (future)  
5. **3 cm TG Module**  
6. **15 mm TG Module** (future)

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
- Internal LO: MAX2870 at 3.9107 GHz (fixed)  
- Mixer: HMC219  
- Output: 0–2.9 GHz

### 3 cm module  
- High‑frequency LO: Doubled analyzer LO (8.94–10.28 GHz)  
- IF LO: ADF4351 (0.56–1.23 GHz)  
- Mixer: HMC220  
- Output: 9.5–11.5 GHz

### 6 cm module (future)  
- Will use analyzer LO + local PLL/multiplier  
- Output expected in 5–7 GHz region

### 15 mm module (future)  
- Will require higher‑order multiplication  
- Output expected in 18–20 GHz region

---

## Block diagram

![TG system architecture](/images/tg-system-architecture.png)

---

## Power distribution & LO levels

| Path | Level | Notes |
|------|------:|-------|
| Analyzer 1st LO → Distribution | +16.5 dBm | Raw analyzer output |
| Distribution → TG modules | +16 dBm | After isolator, amp, splitter, pad |
| TG module LO input | +13 dBm | After on‑module pad/filter |
| Base‑Band MAX2870 LO | +13 dBm | After LO chain |
| 3 cm Doubled LO | +7 dBm | After LO amp |
| 3 cm IF LO (ADF4351) | 0 dBm | Direct |

All levels are chosen to meet mixer LO drive requirements and maintain isolation.

---

## Control architecture

### MCU responsibilities  
- Program MAX2870 (Base‑Band)  
- Program ADF4351 (3 cm)  
- Compute sweep‑dependent IF for 3 cm module  
- Manage LO enable/mute  
- Monitor PLL lock‑detect  
- Handle band selection  
- Provide calibration hooks

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
- Per‑band flatness correction  
- Optional calibration tables stored in MCU flash

System‑level calibration ensures:

- Consistent output level across bands  
- Flatness across each module’s span  
- Coherent phase relationship with analyzer LO

---

## Mechanical / layout considerations

- LO Distribution board placed closest to analyzer LO input  
- TG modules arranged to minimize LO crosstalk  
- Shielding around mixers, doublers, and LO amplifiers  
- Consistent grounding across all modules  
- SMA connectors clearly labeled by band  
- Adequate thermal margin for LO amplifiers and PLLs

---

## Future expansion

The architecture is designed to scale to:

- Additional TG bands  
- Higher‑order multipliers  
- Higher‑frequency PLLs  
- Optional LO monitoring ports  
- Optional TG output leveling loops  
- Optional digital predistortion for flatness correction

The analyzer’s 1st LO and 10 MHz reference remain the **single point of coherence** for the entire TG system.
