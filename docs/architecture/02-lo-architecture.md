# LO Architecture  
**Sources:** Analyzer 1st LO, Analyzer 10 MHz reference  
**Internal LOs:** MAX2870 (Base‑Band), ADF4351 (3 cm), future 6 cm / 15 mm  
**Distribution:** Central RF SA‑LO Distribution board  
**Modes:** Fundamental mixing (Base‑Band), 3× harmonic mixing (3 cm), future bands

---

## Overview

The Tracking Generator system derives all timing and frequency coherence from the spectrum analyzer’s internal LO system.  
Two analyzer signals form the foundation:

- 1st LO (swept, ~3.0–6.8 GHz from the internal synthesizer)  
- 10 MHz reference (system clock)

The TG system uses these to generate:

- Base‑Band LO (fixed 3.9107 GHz)  
- 3 cm IF LO (ADF4351, 0.56–1.23 GHz)  
- 3 cm high‑frequency LO (doubled analyzer LO)  
- Future 6 cm and 15 mm LOs

All TG modules remain phase‑coherent with the analyzer because every LO path ultimately derives from the analyzer’s 1st LO and 10 MHz reference.

---

## LO sources

### Analyzer 1st LO  
- Synthesizer range: ~3.0–6.8 GHz  
- Effective LO range used by TG: 4.47–5.14 GHz (3 cm band)  
- Level: ~+16.5 dBm  
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

The analyzer 1st LO enters the system through the RF SA‑LO Distribution Module, which performs:

- Input isolation  
- Broadband amplification  
- Signal splitting (Wilkinson, relays, or MMIC)  
- Per‑branch level trimming

Each TG module receives:

- LO IN: +16 dBm nominal  
- After on‑module pad/filter: +13 dBm at mixer LO pin

This ensures consistent LO drive for all mixers (HMC219, HMC220, future devices).

---

# How the analyzer generates LO_SA in the 3 cm band

The HP 8562A/B uses a two‑step LO scheme with harmonic generation for the higher bands.  
The relevant internal frequencies from the block diagram are:

- First IF: IF1 = 3.910 GHz  
- First LO (effective): LO1 = 3 × LO_synth (×6 then ÷2)  
- Final IF path (down to 3.1 MHz) is handled by later stages

For the first conversion, the analyzer uses:

IF1 = LO1 – RF_SA

Rearranged:

LO1 = RF_SA + IF1

With IF1 = 3.910 GHz:

LO1 = RF_SA + 3.910 GHz

The analyzer generates LO1 as the 3rd harmonic of the synthesizer output:

LO1 = 3 × LO_synth

So:

3 × LO_synth = RF_SA + 3.910 GHz

Therefore:

LO_synth = (RF_SA + 3.910 GHz) / 3

For the 3 cm RF band used by the TG:

RF_SA = 9.5–11.5 GHz

This gives:

LO_synth_min = (9.5 GHz + 3.910 GHz) / 3 = 13.41 GHz / 3 ≈ 4.47 GHz  
LO_synth_max = (11.5 GHz + 3.910 GHz) / 3 = 15.41 GHz / 3 ≈ 5.14 GHz

So the analyzer’s synthesizer output (the LO we tap for the TG) runs from:

LO_SA = 4.47–5.14 GHz

This is the actual 1st‑LO range the TG must track in the 3 cm band.

Because the TG derives all of its internal LOs from:

- the analyzer’s 1st LO (LO_SA = 4.47–5.14 GHz in the 3 cm band)  
- the analyzer’s 10 MHz reference  

every TG output is inherently phase‑coherent with the analyzer’s sweep.

---

# Harmonic‑mode coherence between analyzer and TG

The HP 8562A/B uses two different mixing modes depending on frequency:

- Fundamental mixing for the Base‑Band TG range (0–2.9 GHz)  
- 3× harmonic mixing (via the ×3 LO chain) for the 3 cm TG range (9.5–11.5 GHz)

In the 3 cm band, the effective relationship between RF_SA and the synthesizer LO_SA is:

LO_SA = (RF_SA + 3.910 GHz) / 3

For RF_SA = 9.5–11.5 GHz, this yields LO_SA = 4.47–5.14 GHz, which is exactly the range used by the TG.

The TG then:

- doubles LO_SA to LO_2 = 2 × LO_SA = 8.94–10.28 GHz  
- generates IF_TG = 0.56–1.23 GHz with the ADF4351  
- uses RF_TG = LO_2 – IF_TG = RF_SA

This ensures that the 3 cm TG output is coherent with the analyzer’s displayed frequency.

---

## LO usage per module

### Base‑Band module  
- Uses analyzer 1st LO as RF input  
- Uses MAX2870 (fixed 3.9107 GHz) as LO input  
- Mixer output: RF_TG = LO_SA – LO_TG = RF_SA  
- Produces 0–2.9 GHz TG output

### 3 cm module  
- Uses analyzer 1st LO (LO_SA = 4.47–5.14 GHz) as input to doubler  
- Doubled LO: 8.94–10.28 GHz → HMC220 LO port  
- ADF4351 generates IF_TG = 0.56–1.23 GHz  
- Mixer output: RF_TG = LO_2 – IF_TG = RF_SA  
- Produces 9.5–11.5 GHz TG output

### 6 cm module (future)  
- Will use analyzer 1st LO as RF or LO input depending on architecture  
- Likely requires:  
  - Local PLL for IF  
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

`file:///images/lo-architecture.png`

---

## Power budget

| Path                         | Stage        | Level   |
|------------------------------|--------------|--------:|
| Analyzer LO → Distribution   | Input        | +16.5 dBm |
| Distribution → TG modules    | After pads   | +16 dBm |
| TG module LO input           | On‑module pad/filter | +13 dBm |
| Base‑Band MAX2870 LO         | After chain  | +13 dBm |
| 3 cm Doubled LO              | After LO amp | +7 dBm  |
| 3 cm IF LO (ADF4351)         | Direct       | 0 dBm   |

Levels vary slightly per module but remain within mixer LO drive requirements.

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
  - Sweep‑dependent IF calculations (3 cm)  
  - Band selection

---

## Mechanical / layout notes

- LO distribution traces are short and well‑shielded  
- High isolation between LO paths and TG RF outputs  
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

The analyzer’s 1st LO and 10 MHz reference remain the single point of coherence for the entire TG system.

