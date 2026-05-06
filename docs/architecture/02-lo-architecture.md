
---

# LO Architecture  
**Sources:** Analyzer 1st LO, Analyzer 10 MHz reference  
**Internal LOs:** MAX2870 (Base‑Band), ADF4351 (3 cm), future 6 cm / 15 mm  
**Distribution:** Central RF SA‑LO Distribution board  
**Modes:** Fundamental mixing (Base‑Band), 3× harmonic mixing (3 cm), future bands

---

## Overview

The Tracking Generator system derives all timing and frequency coherence from the **spectrum analyzer’s internal LO system**.  
Two analyzer signals form the foundation:

- **1st LO** (swept, 3.9–6.8 GHz)  
- **10 MHz reference** (system clock)

The TG system uses these to generate:

- Base‑Band LO (fixed 3.9107 GHz)  
- 3 cm IF LO (ADF4351, 0.56–1.23 GHz)  
- 3 cm high‑frequency LO (doubled analyzer LO)  
- Future 6 cm and 15 mm LOs

All TG modules remain phase‑coherent with the analyzer because **every LO path ultimately derives from the analyzer’s 1st LO and 10 MHz reference**.

---

## LO sources

### Analyzer 1st LO  
- Frequency: **3.9–6.8 GHz**  
- Level: **~+16.5 dBm**  
- Sweep‑synchronous  
- Defines the TG output frequency for all modules

### Analyzer 10 MHz reference  
- Used by:  
  - MAX2870 (Base‑Band)  
  - ADF4351 (3 cm)  
  - Future PLLs  
- Ensures long‑term frequency stability and coherence

---

## LO distribution

The analyzer 1st LO enters the system through the **RF SA‑LO Distribution Module**, which performs:

- Input isolation  
- Broadband amplification  
- Signal splitting (Wilkinson, relays, or MMIC)
- Per‑branch level trimming

Each TG module receives:

- **LO IN:** +16 dBm nominal  
- After on‑module pad/filter:  
  → **+13 dBm at mixer LO pin**

This ensures consistent LO drive for all mixers (HMC219, HMC220, future devices).

---

## LO usage per module

### Base‑Band module  
- Uses analyzer 1st LO as **RF input**  
- Uses MAX2870 (fixed 3.9107 GHz) as **LO input**  
- Mixer output:  
  `RF_TG = LO_SA – LO_TG = RF_SA`  
- Produces **0–2.9 GHz** TG output

### 3 cm module  
- Uses analyzer 1st LO (fundamental) as **input to doubler**  
- Doubled LO: **8.94–10.28 GHz** → HMC220 LO port  
- ADF4351 generates **IF_TG = 0.56–1.23 GHz**  
- Mixer output:  
  `RF_TG = LO_2 – IF_TG = RF_SA`  
- Produces **9.5–11.5 GHz** TG output

### 6 cm module (future)  
- Will use analyzer 1st LO as RF or LO input depending on architecture  
- Likely requires:  
  - Loacl PLL for IF  
  - Frequency multiplication for LO  
  - Band‑specific filtering

### 15 mm module (future)  
- Similar architecture to 6 cm but at higher LO frequencies  
- May require:  
  - ×3 or ×4 multiplication  
  - High‑frequency gain blocks  
  - Tight shielding and isolation

---

## Block diagram

```markdown
![LO architecture](/images/lo-architecture.png)
```

---

## Power budget

| Path | Stage | Level |
|------|--------|------:|
| Analyzer LO → Distribution | Input | +16.5 dBm |
| Distribution → TG modules | After pads | +16 dBm |
| TG module LO input | On‑module pad/filter | +13 dBm |
| Base‑Band MAX2870 LO | After chain | +13 dBm |
| 3 cm Doubled LO | After LO amp | +7 dBm |
| 3 cm IF LO (ADF4351) | Direct | 0 dBm |

Levels vary slightly per module but remain within mixer LO drive requirements.

---

## Control architecture

- All PLLs (MAX2870, ADF4351, future devices) lock to the analyzer’s **10 MHz reference**  
- MCU programs:  
  - MAX2870 (Base‑Band)  
  - ADF4351 (3 cm)  
  - Future PLLs  
- MCU handles:  
  - LO enable/mute  
  - Lock‑detect monitoring  
  - Sweep‑dependent IF calculations (3 cm)  
  - Band selection

---

## Mechanical / layout notes

- LO distribution traces are short and well‑shielded  
- High isolation between LO paths and TG RF outputs  
- Proper via fencing around mixers and multipliers  
- Maintain thermal margin for LO amplifiers  
- Consistent grounding across all TG modules  

---

## Future expansion

The LO architecture is designed to scale to:

- 6 cm and 15 mm TG modules  
- Higher‑order multipliers  
- Additional PLLs  
- Optional LO mute switching  
- Optional LO monitoring ports

The analyzer’s 1st LO and 10 MHz reference remain the **single point of coherence** for the entire TG system.

---

