# 15 mm Tracking Generator Module (concept)  
**RF Output:** 23.0–25.0 GHz (option band, includes 24.048 GHz amateur)  
**Harmonic Mode:** n = 4  
**Mixer Core:** mm‑wave mixer (22–26 GHz class)  
**TG IF LO:** ADF4351 (fixed 310.7 MHz)  
**SA LO Path:** Quadrupled analyzer LO (≈22.3–26.3 GHz)

---

## Overview

The 15 mm module is a **conceptual future TG path** extending coherent tracking into the 23–25 GHz option band.  
It operates in the analyzer’s **4× harmonic mixing mode** and derives all timing from:

- **Analyzer LO_SA** (fundamental synthesizer output)  
- **10 MHz reference**

The module uses:

- A **×4 LO chain** derived from the analyzer LO_SA as the mm‑wave LO  
- A **fixed‑frequency ADF4351** at 310.7 MHz as the IF LO  
- A mm‑wave mixer to produce the final RF output via the difference product

The 24.048 GHz amateur allocation lies inside this TG band.

---

## Frequency plan

### Analyzer‑derived quantities  
`RF_SA = 2 * V_sweep`  
`IF_SA = 310.7 MHz`  
`n = 4`

### Analyzer LO (fundamental synthesizer output)  

Harmonic‑mode relation:  
`IF_SA = | 4 * LO_SA – RF_SA |`

Analyzer uses the **high‑side** solution:  
`LO_SA = (RF_SA + 0.3107 GHz) / 4`

For RF_SA = 22.0–26.0 GHz:

- `LO_SA,min = (23.0 + 0.3107) / 4 ≈ 5.8277 GHz`  
- `LO_SA,max = (25.0 + 0.3107) / 4 ≈ 6.3277 GHz`

So the analyzer LO delivered to the TG is:

- **LO_SA ≈ 5.82–6.32 GHz**

At the 15 mm amateur allocation (24.048 GHz):

- `LO_SA ≈ (24.048 + 0.3107) / 4 ≈ 6.0897 GHz`

---

### Quadrupled LO for mm‑wave mixer LO port  

We choose:

`LO_4 = 4 * LO_SA = RF_SA + 0.3107 GHz`

So for RF_SA = 22.0–26.0 GHz:

- `LO_4 ≈ 22.3107–26.3107 GHz`

This is the **mm‑wave LO** applied to the mixer LO port.

---

### TG IF LO (ADF4351)  

Mixer uses:  
`RF_TG = LO_4 – IF_TG = RF_SA`

Since `LO_4 = RF_SA + 310.7 MHz`,  
we require:  
`IF_TG = 310.7 MHz` (constant)

Thus the ADF4351 again runs at a **fixed 310.7 MHz**, same control model as 6 cm and 3 cm.

---

## Block diagram

![15mm TG architecture](/images/15mm.png)

---

## Power budget (nominal, 15 mm module – concept)

Same assumptions as before, but with updated frequency ranges:

```
## Power budget (nominal, 15 mm module – concept)

| Stage                              | Frequency               | ΔdB     | Level   |
|------------------------------------|------------------------:|--------:|--------:|
| **LO path**                        |                         |         |         |
| SA LO output                       | 5.58–6.58 GHz           |   0 dB  | +16 dBm |
| LO isolator                        | 5.58–6.58 GHz           |  –1 dB  | +15 dBm |
| ×2 multiplier #1 input             | 5.58–6.58 GHz           |   0 dB  | +15 dBm |
| ×2 multiplier #1 (conv. –15 dB)    | 11.16–13.16 GHz         | –15 dB  |   0 dBm |
| LO amp #1                          | 11.16–13.16 GHz         | +15 dB  | +15 dBm |
| ×2 multiplier #2 input             | 11.16–13.16 GHz         |   0 dB  | +15 dBm |
| ×2 multiplier #2 (conv. –15 dB)    | 22.3–26.3 GHz           | –15 dB  |   0 dBm |
| LO amp #2                          | 22.3–26.3 GHz           | +15 dB  | +15 dBm |
| LO pad to mixer LO port            | 22.3–26.3 GHz           |  –2 dB  | +13 dBm |
| LO at mixer LO port                | 22.3–26.3 GHz           |   0 dB  | +13 dBm |
|                                    |                         |         |         |
| **IF path**                        |                         |         |         |
| ADF4351 IF output                  | 310.7 MHz               |   0 dB  |  +2 dBm |
| IF filter                          | 310.7 MHz               |  –1 dB  |  +1 dBm |
| IF amplifier                       | 310.7 MHz               | +20 dB  | +21 dBm |
| IF pad (to mixer IF port)          | 310.7 MHz               | –14 dB  |  +7 dBm |
| IF at mixer IF port                | 310.7 MHz               |   0 dB  |  +7 dBm |
|                                    |                         |         |         |
| **RF path**                        |                         |         |         |
| Mixer RF out (nominal, conv. –8 dB)| 22.0–26.0 GHz           |  –8 dB  |  ~5 dBm |
| RF pad / EQ                        | 22.0–26.0 GHz           |  –5 dB  |   0 dBm |
| RF output (SMA / waveguide launch) | 22.0–26.0 GHz           |   0 dB  |   0 dBm |
```

**NOTE:** These are **design targets**, not commitments. Real parts will move the numbers a bit.

