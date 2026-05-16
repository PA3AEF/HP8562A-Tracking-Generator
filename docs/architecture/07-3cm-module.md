# 3 cm Tracking Generator Module  
**RF Output:** 9.5–11.5 GHz (2 GHz span)  
**Harmonic Mode:** n = 2  
**Mixer Core:** HMC220  
**TG IF LO:** ADF4351 (fixed 310.7 MHz)  
**SA LO Path:** Doubled analyzer LO (9.81–11.81 GHz)

---

## Overview

The 3 cm module generates a tracking‑synchronous RF output in the 9.5–11.5 GHz range.  
It operates in the analyzer’s **2× harmonic mixing mode** and derives all timing from:

- **V_sweep**  
- **Analyzer LO_SA** (fundamental synthesizer output)  
- **10 MHz reference**

The module uses:

- A **doubled analyzer LO** as the high‑frequency LO for the HMC220  
- A **fixed‑frequency ADF4351** at 310.7 MHz as the IF LO  
- An HMC220 mixer to produce the final RF output via the difference product

This module forms the primary **X‑band TG path** in the system.

---

## Frequency plan

### Analyzer‑derived quantities  
`RF_SA = 2 * V_sweep`  
`IF_SA = 310.7 MHz`  
`n = 2`

### Analyzer LO (fundamental synthesizer output)  
Harmonic‑mode relation:  
`IF_SA = | 2 * LO_SA – RF_SA |`

Analyzer uses the **high‑side** solution:  
`LO_SA = (RF_SA + 310.7 MHz) / 2`

For RF_SA = 9.5–11.5 GHz:  
`LO_SA = 4.905–5.905 GHz`

This is the **actual analyzer LO** delivered to the TG distribution board.

---

### Doubled LO for HMC220 LO port  
`LO_2 = 2 * LO_SA`  → `9.8107–11.8107 GHz`

This is the **high‑frequency LO** applied to the HMC220 LO port.

---

### TG IF LO (ADF4351)  
Mixer uses:  
`RF_TG = LO_2 – IF_TG = RF_SA`

Since `LO_2 = RF_SA + 310.7 MHz`,  
we require:  
`IF_TG = 310.7 MHz` (constant)

Thus the ADF4351 runs at a **fixed 310.7 MHz**, simplifying control and calibration.

---

## Block diagram

```
![3cm TG architecture](/images/3cm.png)
```

---

## Power budget (nominal)

| Stage                         | Frequency             | ΔdB     | Level   |
|-------------------------------|----------------------:|--------:|--------:|
| **LO path**                   |                       |         |         |
| SA LO output                  | 4.905–5.905 GHz       |   0 dB  | +16 dBm |
| LO isolator                   | 4.905–5.905 GHz       |  –1 dB  | +15 dBm |
| LO doubler input              | 4.905–5.905 GHz       |   0 dB  | +15 dBm |
| LO doubler (HMC204)           | 9.81–11.81 GHz   | –18 dB  |  –3 dBm |
| LO amplifier                  | 9.81–11.81 GHz        | +18 dB  | +15 dBm |
| LO pad to mixer LO port       | 9.81–11.81 GHz        |  –2 dB  | +13 dBm |
| LO at mixer LO port           | 9.81–11.81 GHz        |   0 dB  | +13 dBm |
|                               |                       |         |         |
| **IF path**                   |                       |         |         |
| ADF4351 IF output             | 310.7 MHz             |   0 dB  |  +2 dBm |
| IF filter                     | 310.7 MHz             |  –1 dB  |  +1 dBm |
| IF amplifier                  | 310.7 MHz             | +20 dB  | +21 dBm |
| IF pad (to mixer IF port)     | 310.7 MHz             | –14 dB  |  +7 dBm |
| IF at mixer IF port           | 310.7 MHz             |   0 dB  |  +7 dBm |
|                               |                       |         |         |
| **RF path**                   |                       |         |         |
| Mixer RF out (nominal)        | 9.5–11.5 GHz          |  –8 dB  |  ~5 dBm |
| RF pad / EQ                   | 9.5–11.5 GHz          |  –5 dB  |   0 dBm |
| RF output (SMA)               | 9.5–11.5 GHz          |   0 dB  |   0 dBm |


Levels are nominal and must be trimmed with pads and EQ for flatness over the 2 GHz span.

---

## Control architecture

### Inputs to MCU  
- `V_sweep` (ADC)  
- 10 MHz reference  
- Band select

### MCU responsibilities  
- Compute `RF_SA = 2 * V_sweep`  
- Program ADF4351 to **fixed 310.7 MHz**  
- Manage LO enable/mute  
- Provide calibration hooks

### SPI layout  
- Shared SPI bus  
- Dedicated CS for ADF4351  
- PLL lock‑detect GPIO

---

## Calibration notes

- Amplitude flatness corrected via output pad/EQ  
- `LO_2` level set by fixed‑gain amplifier  
- ADF4351 spur performance acceptable due to low IF offset  
- Mixer conversion loss measured per module and stored in calibration table  
- No IF sweep required (fixed 310.7 MHz simplifies calibration)

---

## Mechanical / layout notes

- Doubler → LO amp → HMC220 LO path should be short and shielded  
- Maintain isolation between `LO_2` and RF output  
- ADF4351 IF routing requires clean 50 Ω but is not microwave‑critical  
- Fine‑tune pads for correct levels at `LO_2`, `IF_TG`, and `RF_TG`  
