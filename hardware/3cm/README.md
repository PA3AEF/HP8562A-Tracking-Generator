# 3 cm Tracking Generator Module (9.5–11.5 GHz)

The 3 cm module is the harmonic‑mode RF upconversion stage of the Tracking Generator.  
It reconstructs the analyzer’s 9.5–11.5 GHz sweep by combining:

- the analyzer’s 1st LO (LO_SA = 4.905–5.905 GHz)  
- the analyzer’s internal IF = 310.7 MHz (harmonic 2 mode)  
- a TG‑generated IF_TG = 310.7 MHz from an ADF4351  
- a doubled version of the analyzer’s 1st LO (LO₂ = 9.81–11.81 GHz) for the HMC220 mixer

All frequencies remain coherent with the analyzer because they are derived from the analyzer’s 1st LO and 10 MHz reference.

---

## Harmonic‑mode coherence

In the 3 cm band, the HP 8562A/B uses **2× harmonic mixing** with an internal IF of **310.7 MHz**.

The analyzer’s 1st LO follows:  
`2 × LO_SA = RF_SA + 310.7 MHz`  →  `LO_SA = (RF_SA + 310.7 MHz) / 2`

For RF_SA = 9.5–11.5 GHz, this yields:  
`LO_SA = 4.905–5.905 GHz`

This is the actual LO range the 3 cm TG module must track.

---

## Why the LO must be doubled

The HMC220 mixer requires:

- IF port: DC–4 GHz  
- LO/RF ports: 5–12 GHz  

The analyzer’s 1st LO (4.905–5.905 GHz) is too low for the HMC220 LO port.  
Therefore, the TG uses a ×2 multipiler (HMC204): `LO₂ = 2 × LO_SA = 9.81–11.81 GHz`, fitting the mixer’s LO range.

---

## IF_TG generation (ADF4351)

The TG generates a fixed IF signal using the ADF4351: `IF_TG = 310.7 MHz`.  
The MCU programs the ADF4351 via SPI and maintains sweep coherence with the analyzer’s 10 MHz reference.

---

## Mixer output and TG coherence

The HMC220 mixer produces: `RF_TG = LO₂ – IF_TG = RF_SA`  
Substituting the ranges:  
LO₂ = 9.81–11.81 GHz, IF_TG = 310.7 MHz → RF_TG = 9.5–11.5 GHz.  
This exactly matches the analyzer’s displayed frequency.

---

## Module architecture and building blocks

### HMC204 Analyzer LO doubler
- Input: LO_SA = 4.905–5.905 GHz  
- Output: LO₂ = 9.81–11.81 GHz  
- Purpose: shift analzer LO into HMC220 LO range while maintaining sweep coherence

### ADF4351 IF_TG generator
- Output: 310.7 MHz (fixed)  
- MCU‑controlled and reference‑locked  
- Purpose: provide the IF offset needed to reconstruct RF_TG

### HMC220 mixer
- LO port: 9.81–11.81 GHz  
- IF port: 310.7 MHz  
- RF port: 9.5–11.5 GHz  
- Purpose: perform the upconversion that produces the 3 cm TG output

### Band‑pass filter (8–12 GHz)
- Removes LO₂ leakage, IF_TG leakage, and mixer images  
- Ensures only the 9.5–11.5 GHz band reaches the amplifier

### RF gain stage + output pad
- Provides ~0 dBm output  
- Maintains linearity across the sweep  
- Ensures stable 50 Ω output at the SMA connector

---

## Performance targets

### Frequency performance
- Output band: 9.5–11.5 GHz  
- Must track analyzer sweep exactly  
- Fast settling to follow analyzer sweep speed

### Amplitude performance
- Target output: ~0 dBm  
- Flatness corrected at system level  
- No compression across sweep

### Spectral purity
- Low LO₂ leakage  
- Low IF_TG leakage  
- Spurs dominated by ADF4351 + multiplier chain  
- Phase noise dominated by analyzer LO

### Implementation constraints
- RF layout suitable for >10 GHz  
- Isolation between LO₂, IF_TG, and RF paths  
- Stable operation across temperature and supply variations
