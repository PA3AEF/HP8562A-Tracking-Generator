# LO Architecture  
**Sources:** Analyzer 1st LO, Analyzer 10 MHz reference  
**Internal LOs:** MAX2870 (Base‑Band), ADF4351 (3 cm), future 6 cm / 12 mm  
**Distribution:** Central RF SA‑LO Distribution module 
**Modes:** Fundamental mixing (Base‑Band), 2× harmonic mixing (3 cm), future bands

---

## Overview

The Tracking Generator system derives all timing and frequency coherence from the spectrum analyzer’s internal LO system.  
Two analyzer signals form the foundation:

- 1st LO (swept, ~2.9–6.8 GHz synthesizer output)  
- 10 MHz reference (system clock)

The TG system uses these to generate:

- Base‑Band LO (fixed 3.9107 GHz)  
- 3 and 6 cm IF LO (ADF4351, fixed 310.7 MHz)  
- 3 cm high‑frequency LO (doubled analyzer LO)  
- Future 12 mm LOs

All TG moduls remain phase‑coherent with the analyzer because every LO path ultimately derives from the analyzer’s 1st LO and 10 MHz reference.

---

## LO sources

### Analyzer 1st LO  
- Synthesizer range: 2.9–6.8 GHz  
- Delivered to TG as the fundamental LO_SA, used by all TG modules  
- **Effective LO_SA range depends on analyzer band and harmonic mode:**  
  - Base‑Band (0–2.9 GHz): harmonic 1, IF = 3.9107 GHz  
  - Mid‑band (2.75–6.46 GHz): harmonic 1, IF = 310.7 MHz 
    - 6 cm (4.4-6.4 GHz): harmonic 1, IF = 310.7 MHz → LO_SA = 4.710–6.710 GHz
  - High-band (5.86-13 GHz): harmonic 2, IF = 310.7 MHz
    - 3 cm (5.86–13 GHz): harmonic 2, IF = 310.7 MHz → LO_SA = 4.905–5.905 GHz
  - High-band-2 (12.4-19.7) GHz): harmonic 3, IF = 310.7 MHz
  - High-band-3 (9.5-11.5 GHz): harmonic 4, IF = 310.7 MHz
    - 12 mm (23–25 GHz): harmonic 4, IF = 310.7 MHz → LO_SA = 5.827–6.327 GHz
- Level: ~+16.5 dBm  
- Sweep‑synchronous  
- Defines the TG output frequency for all modules  
- For detailed internal LO generation, see **Analyzer LO Internals (3 cm Band)**

---

## LO distribution

The analyzer 1st LO enters the system through the RF SA‑LO Distribution Module, which performs:

- Input isolation  
- Broadband amplification  
- Signal splitting (Wilkinson, relays, or MMIC)  

Each TG module receives:

- LO IN: +16 dBm nominal  
- After on‑module pad/filter: ~+13 dBm at mixer input

This ensures consistent LO drive for all mixers (HMC219, HMC220, future devices).

---

# How the analyzer generates LO_SA in the 3 cm band

The HP 8562A/B uses **harmonic mixing mode n = 2** with a fixed IF of 310.7 MHz for the 5.86–13 GHz band.  
The internal first‑conversion relationship is:

`IF_SA = | 2 × LO_SA – RF_SA |`

Analyzer uses the high‑side solution:

`LO_SA = (RF_SA + 310.7 MHz) / 2`

For RF_SA = 9.5–11.5 GHz:

- LO_SA_min = 4.905 GHz  
- LO_SA_max = 5.905 GHz  

Thus the analyzer’s synthesizer output (the LO delivered to the TG distribution board) runs from:

**LO_SA = 4.905–5.905 GHz**

Because the TG derives all of its internal LOs from:

- the analyzer’s 1st LO (LO_SA = 4.905–5.905 GHz)  
- the analyzer’s 10 MHz reference  

every TG output is inherently phase‑coherent with the analyzer’s sweep.

---

# Harmonic‑mode coherence between analyzer and TG

The HP 8562A/B uses two mixing modes relevant to the TG:

- Fundamental mixing for the Base‑Band TG range (0–2.9 GHz)  
- **2× harmonic mixing** for the 3 cm TG range (9.5–11.5 GHz)

In the 3 cm band, the effective relationship between RF_SA and the synthesizer LO_SA is:

`LO_SA = (RF_SA + 310.7 MHz) / 2`

The TG then:

- doubles LO_SA to `LO_2 = 2 × LO_SA = RF_SA + 310.7 MHz`  
- uses a fixed IF_TG = 310.7 MHz  
- produces `RF_TG = LO_2 – IF_TG = RF_SA`

This ensures that the 3 cm TG output is coherent with the analyzer’s displayed frequency.

---

## LO usage per module

### Base‑Band module  
- Uses analyzer 1st LO as RF input  
- Uses MAX2870 (fixed 3.9107 GHz) as LO input  
- Mixer output: `RF_TG = LO_SA – LO_TG = RF_SA`  
- Produces 0–2.9 GHz TG output

### 6 cm module (future)  
- Uses analyzer 1st LO (LO_SA = 4.710–6.710 GHz) 
- Direct LO (4.710–6.710 GHz) → HMC220 LO port  
- ADF4351 generates fixed `IF_TG = 310.7 MHz`  
- Mixer output: `RF_TG = LO_2 – IF_TG = RF_SA`  
- Produces 4.4-6.4 GHz TG output

### 3 cm module  
- Uses analyzer 1st LO (LO_SA = 4.905–5.905 GHz) as input to doubler  
- Doubled LO: `LO_2 = 9.8107–11.8107 GHz` → HMC220 LO port  
- ADF4351 generates fixed `IF_TG = 310.7 MHz`  
- Mixer output: `RF_TG = LO_2 – IF_TG = RF_SA`  
- Produces 9.5–11.5 GHz TG output

### 12 mm module (future)  
- Similar architecture to 3 cm but at higher LO frequencies  
- May require:  
  - ×3 or ×4 multiplication  
  - High‑frequency gain blocks  
  - Tight shielding and isolation

---

## Reference Selection: 10 MHz vs. 300 MHz

The analyzer provides two possible reference signals:  
- **10 MHz TCXO** (primary timebase)  
- **300 MHz PLL output** (derived from the 10 MHz)

For the TG architecture, the **10 MHz reference is preferred**.

### Why 10 MHz is the correct choice
- The 10 MHz TCXO is the analyzer’s **master clock**.  
- The 300 MHz signal is generated by a **PLL locked to this 10 MHz**, so it carries **extra phase noise and spurs**.  
- MAX2870 and ADF4351 both accept low‑frequency references directly and internally divide as needed.  
- Using 300 MHz would require dividing it down anyway, giving **no benefit** and **worse noise**.  
- Locking to 10 MHz keeps the TG **coherent** with the analyzer, including when the analyzer is locked to an **external 10 MHz reference**.

Therfore, all TG PLLs use the analyzer’s **10 MHz TCXO** as their reference.  
It is cleaner, simpler, and guarantees long‑term coherence with the analyzer’s LO system.

---

## Power budget (Generic)

| Path                         | Stage        | Level   |
|------------------------------|--------------|--------:|
| Analyzer LO → Distribution   | Input        | +16.5 dBm |
| Distribution → TG modules    | After pads   | +16 dBm |
| TG module LO input           | On‑module pad/filter | +13 dBm |
| Base‑Band MAX2870 LO         | After chain  | +13 dBm |
| 3 cm Doubled LO              | After LO amp | +7 dBm  |
| 3 cm IF LO (ADF4351)         | Direct       | 0 dBm   |

Levels may vary slightly per module but remain withjin mixer LO drive requirements.

---

## Control architecture

- All PLLs (MAX2870, ADF4351, future devices) lock to the analyzer’s 10 MHz reference  
- MCU programs:  
  - MAX2870 (Base‑Band)  
  - ADF4351 (3 cm)  
  - Future PLLs  
- MCU handles:  
  - LO enable/mute  
  - Lock‑detect monitoring
  - 10 MHz reference monitoring  
  - Sweep‑dependent IF calculations (Base‑Band only)  
  - Band selection

---

## Mechanical / layout notes

- LO distribution is short and well‑shielded  
- High isolation between LO paths and TG RF outputs    
- Consistent grounding across all TG modules  

---

## Future expansion

The LO architecture is designed to scale to:

- 12 mm TG module
- Higher‑order multipliers  
- Additional PLLs  
- Optional LO mute switching  
- Optional LO monitoring ports

The analyzer’s 1st LO and 10 MHz reference remain the single point of coherence for the entire TG system.

---