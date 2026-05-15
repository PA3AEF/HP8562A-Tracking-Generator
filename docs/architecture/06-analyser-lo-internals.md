# Analyzer LO Internals (3 cm Band)  
**Purpose:** Explain how the HP 8562A/B analyzer generates the 4.905–5.905 GHz 1st LO range used by the Tracking Generator.

---

## Overview

In the 3 cm band (5.86–13 GHz), the HP 8562A/B operates in **harmonic mixing mode n = 2** and uses a **fixed first IF of 310.7 MHz**.  
Bands 1–4 (including 3 cm) use a **double‑conversion architecture**:

- **First conversion:** RF → 310.7 MHz  
- **Final conversion:** 310.7 MHz → 10.7 MHz  

The TG locks onto the analyzer’s **fundamental synthesizer output LO_SA**, which runs from **4.905–5.905 GHz** for RF_SA = 9.5–11.5 GHz.

This LO_SA range is derived from the harmonic‑mode equation:

**IF_SA = | 2 × LO_SA – RF_SA |**,  
with **IF_SA = 310.7 MHz**.

The analyzer uses the **high‑side** solution:

**LO_SA = (RF_SA + 310.7 MHz) / 2**

---

## Internal signal flow

1. **RF_SA (9.5–11.5 GHz)** enters the **A8 Dual Mixer**.  
2. The analyzer’s **LO_synth** (4.905–5.905 GHz) is **doubled** internally to produce **2 × LO_synth = 9.81–11.81 GHz**.  
3. The first mixer down‑converts RF_SA to the **first IF = 310.7 MHz** (harmonic mode n = 2).  
4. The 310.7 MHz IF passes through the **A13 Second Converter**, but **bypasses its mixer** (Bands 1–4 do not use the second conversion).  
5. The **A15 Third Converter** performs the **final conversion** from 310.7 MHz to the **final IF = 10.7 MHz**, which feeds the display chain.

So according to the HP service manual:

> “Bands 1 through 4 use double conversion…  
> A Dual Mixer down‑converts the RF input to a first IF of 310.7 MHz…  
> The second and final conversion occurs in the third converter… producing the final 10.7 MHz IF.”

---

## Frequency relationships

### First conversion  
`IF_SA = | 2 * LO_SA – RF_SA |`

Analyzer uses the **high‑side** branch:

`2 * LO_SA = RF_SA + 310.7 MHz`  
`LO_SA = (RF_SA + 310.7 MHz) / 2`

### For RF_SA = 9.5–11.5 GHz  
- LO_SA_min = (9.5 + 0.3107) / 2 = **4.905 GHz**  
- LO_SA_max = (11.5 + 0.3107) / 2 = **5.905 GHz**

Thus the analyzer’s synthesizer output (LO_SA) runs from:

**LO_SA = 4.905–5.905 GHz**

This is the LO range distributed to the TG.

---

## Summary table

| Parameter | Symbol | Value / Range | Notes |
|-----------|--------|---------------:|-------|
| Displayed RF band | **RF_SA** | 9.5–11.5 GHz | Analyzer 3 cm band |
| First IF | **IF_SA** | 310.7 MHz | Fixed internal IF |
| Synthesizer output | **LO_SA** | 4.905–5.905 GHz | TG reference |
| Effective 1st LO | **LO1** | 9.81–11.81 GHz | 2 × LO_SA |
| Final IF | **IF_display** | 10.7 MHz | Display IF |

---

## Integration with TG

The TG uses this LO_SA range to maintain coherence:

- Doubled LO:  
  **LO_2 = 2 × LO_SA = 9.8107–11.8107 GHz**  
- IF_TG (ADF4351):  
  **IF_TG = 310.7 MHz** (fixed)  
- Mixer output:  
  **RF_TG = LO_2 – IF_TG = RF_SA**

This ensures perfect frequency tracking between analyzer and TG.

