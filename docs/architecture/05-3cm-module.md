
---

# 3 cm Tracking Generator Module  
**RF Output:** 9.5–11.5 GHz (2 GHz span)  
**Harmonic Mode:** n = 3  
**Mixer Core:** HMC220  
**TG IF LO:** ADF4351 (0.56–1.23 GHz)  
**SA LO Path:** Doubled analyzer LO (8.94–10.28 GHz)

---

## Overview

The 3 cm module generates a tracking‑synchronous RF output in the 9.5–11.5 GHz range.  
It operates in the analyzer’s 3× harmonic mixing mode and derives all timing from:

- `V_sweep`  
- Analyzer `LO_SA` (fundamental)  
- 10 MHz reference

The module uses:

- A **doubled analyzer LO** as the high‑frequency LO for the HMC220  
- An **ADF4351** as the low‑frequency IF LO  
- An HMC220 mixer to produce the final RF output via the difference product

This module forms the **primary X‑band TG path** in the system.

---

## Frequency plan

### Analyzer‑derived quantities  
`RF_SA = 2 * V_sweep`  
`IF_1 = 3.9107 GHz`

### Analyzer LO (fundamental)  
`LO_SA = (RF_SA + IF_1) / 3`

### Doubled LO for HMC220 LO port  
`LO_2 = 2 * LO_SA`  
→ `8.94–10.28 GHz`

This is the **high‑frequency LO** applied to the HMC220 LO port.

### TG IF LO (ADF4351)  
Mixer uses:  
`RF_TG = LO_2 - IF_TG = RF_SA`

Thus:  
`IF_TG = (2 * IF_1 - RF_SA) / 3`  
→ `0.56–1.23 GHz`

This is the **ADF4351 output frequency**.

---

## Block diagram

```markdown
![3cm TG architecture](/images/3cm.png)
```

---

## Power budget (nominal)

| Stage              | Frequency          | Level    |
|--------------------|-------------------|---------:|
| SA LO input        | 4.47–5.14 GHz     | ~0 dBm   |
| Doubler output     | 8.94–10.28 GHz    | –6 dBm   |
| LO amplifier       | 8.94–10.28 GHz    | +7 dBm   |
| ADF4351 IF (IF_TG) | 0.56–1.23 GHz     | 0 dBm    |
| Mixer RF out       | 9.5–11.5 GHz      | –8 dBm   |
| RF amplifier       | 9.5–11.5 GHz      | +7 dBm   |
| Output pad / EQ    | 9.5–11.5 GHz      | 0 dBm    |

Levels are nominal and may be trimmed with pads and EQ for flatness over the 2 GHz span.

---

## Control architecture

### Inputs to MCU  
- `V_sweep` (ADC)  
- 10 MHz reference  
- Band select

### MCU responsibilities  
- Compute `RF_SA = 2 * V_sweep`  
- Compute `IF_TG = (2 * IF_1 - RF_SA) / 3`  
- Program ADF4351 via SPI  
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

---

## Mechanical / layout notes

- Doubler → LO amp → HMC220 LO path should be short and shielded  
- Maintain isolation between `LO_2` and RF output  
- ADF4351 IF routing requires clean 50 Ω but is not microwave‑critical  
- Fine‑tune pads for correct levels at `LO_2`, `IF_TG`, and `RF_TG`  
- Use X‑band‑appropriate substrate and via fencing around the mixer  

---

