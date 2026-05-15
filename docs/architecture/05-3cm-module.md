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

| Stage                    | Frequency            | Level    |
|--------------------------|---------------------:|---------:|
| SA LO input              | 4.905–5.905 GHz      | 16 dBm   |
| Doubler output (HMC204)  | 9.81–11.81 GHz       | –2 dBm   |
| LO amplifier + Pad       | 9.81–11.81 GHz       | +13 dBm  |
| ADF4351 IF (IF_TG)       | 310.7 MHz            | +2 dBm   |
| Mixer RF out             | 9.5–11.5 GHz         | ~5 dBm   |
| Output pad / EQ          | 9.5–11.5 GHz         | 0 dBm    |

Levels are nominal and may be trimmed with pads and EQ for flatness over the 2 GHz span.

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
