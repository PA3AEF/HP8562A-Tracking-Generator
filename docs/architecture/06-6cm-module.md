# 6 cm Tracking Generator Module  
**RF Output:** 4.4–6.4 GHz (2 GHz span)  
**Harmonic Mode:** n = 1  
**Mixer Core:** HMC219
**TG IF LO:** ADF4351 (fixed 310.7 MHz)  
**SA LO Path:** Analyzer LO_SA (4.7107–6.7107 GHz)

---

## Overview

The 6 cm module generates a tracking‑synchronous RF output in the 4.4–6.4 GHz range.  
It operates in the analyzer’s **fundamental mixing mode (n = 1)** and derives all timing from:

- **V_sweep**  
- **Analyzer LO_SA** (fundamental synthesizer output)  
- **10 MHz reference**

The module uses:

- The **analyzer LO_SA directly** as the mixer LO  
- A **fixed‑frequency ADF4351** at 310.7 MHz as the IF LO  
- An HMC219/HMC220 mixer to produce the final RF output via the difference product

This module forms the primary **C‑band TG path** in the system.

---

## Frequency plan

### Analyzer‑derived quantities  
`RF_SA = 2 * V_sweep`  
`IF_SA = 310.7 MHz`  
`n = 1`

### Analyzer LO (fundamental synthesizer output)  
Harmonic‑mode relation:  
`IF_SA = | LO_SA – RF_SA |`

Analyzer uses the **high‑side** solution:  
`LO_SA = RF_SA + 0.3107 GHz`

Zero‑span measurements confirm:  
`LO_SA = 4.7107–6.7107 GHz`

This is the **actual analyzer LO** delivered to the TG distribution board.

---

### Mixer LO (direct analyzer LO)  
The mixer LO port receives:  
`LO_SA = 4.7107–6.7107 GHz`

This range is compatible with the HMC219 LO port.

---

### TG IF LO (ADF4351)  
Mixer uses:  
`RF_TG = LO_SA – IF_TG = RF_SA`

Since `LO_SA = RF_SA + 310.7 MHz`,  
we require:  
`IF_TG = 310.7 MHz` (constant)

Thus the ADF4351 runs at a **fixed 310.7 MHz**, simplifying control and calibration.

---

## Block diagram

```
![6cm TG architecture](/images/6cm.png)
```

---

## Power budget (nominal)

| Stage                     | Frequency            | ΔdB    | Level   |
|---------------------------|---------------------:|-------:|--------:|
| **LO path**               |                      |        |         |
| SA LO output              | 4.71–6.71 GHz        |   0 dB | +16 dBm |
| LO isolator               | 4.71–6.71 GHz        |  –1 dB | +15 dBm |
| LO pad / buffer input     | 4.71–6.71 GHz        |  –2 dB | +13 dBm |
| LO at mixer LO port       | 4.71–6.71 GHz        |   0 dB | +13 dBm |
| Mixer LO‑to‑RF isolation  | 4.4–6.4 GHz          |  —     | (spec)  |
|                           |                      |        |         |
| **IF path**               |                      |        |         |
| ADF4351 IF output         | 310.7 MHz            |   0 dB |  +2 dBm |
| IF filter                 | 310.7 MHz            |  –1 dB |  +1 dBm |
| IF amplifier              | 310.7 MHz            | +20 dB | +21 dBm |
| IF pad (to mixer IF port) | 310.7 MHz            | –14 dB |  +7 dBm |
| IF at mixer IF port       | 310.7 MHz            |   0 dB |  +7 dBm |
|                           |                      |        |         |
| **RF path**               |                      |        |         |
| Mixer RF out (nominal)    | 4.4–6.4 GHz          |  –8 dB |  ~5 dBm |
| RF pad / EQ               | 4.4–6.4 GHz          |  –5 dB |   0 dBm |
| RF output (SMA)           | 4.4–6.4 GHz          |   0 dB |   0 dBm |


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
- LO_SA level set by fixed‑gain buffer  
- ADF4351 spur performance acceptable due to low IF offset  
- Mixer conversion loss measured per module and stored in calibration table  
- No IF sweep required (fixed 310.7 MHz simplifies calibration)

---

## Mechanical / layout notes

- LO_SA → mixer LO path should be short and shielded  
- Maintain isolation between LO_SA and RF output  
- ADF4351 IF routing requires clean 50 Ω but is not microwave‑critical  
- Fine‑tune pads for correct levels at `LO_SA`, `IF_TG`, and `RF_TG`  
