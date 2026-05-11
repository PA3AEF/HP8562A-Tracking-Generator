# 3 cm Tracking Generator Module (9.5–11.5 GHz)

The 3 cm module is the harmonic‑mode RF upconversion stage of the Tracking Generator.  
It reconstructs the analyzer’s 9.5–11.5 GHz sweep by combining:

- the analyzer’s 1st LO  
- the analyzer’s 3.1 MHz IF (used in harmonic mode)  
- a TG‑generated IF_TG from an ADF4351  
- a doubled version of the analyzer’s 1st LO (to satisfy HMC220 mixer limits)

All frequencies remain coherent with the analyzer because they are derived from the analyzer’s 1st LO and 10 MHz reference.

---

## Harmonic‑mode coherence

In the 3 cm band, the HP 8562A/B uses 3× harmonic mixing with an internal IF of 3.1 MHz.

The analyzer’s 1st LO follows:  3 * LO_SA = RF_SA + 3.1 MHz

For the analyzer’s 3 cm RF band:  RF_SA = 9.5–11.5 GHz

Therefore:  LO_SA = (RF_SA + 3.1 MHz) / 3

Which evaluates to:  LO_SA = 4.47–5.14 GHz

This is the actual LO range the 3 cm TG module must track.

---

## Why the LO must be doubled

The HMC220 mixer requires:

- IF port: DC–4 GHz  
- LO/RF ports: 5–12 GHz  

The analyzer’s 1st LO (4.47–5.14 GHz) is too low for the HMC220 LO port.

Therefore the TG uses a ×2 multiplier:  LO_2 = 2 * LO_SA

Which yields into: LO_2 = 8.94–10.28 GHz

This fits the HMC220 LO port range.

---

## IF_TG generation (ADF4351)

The TG generates a low‑GHz IF signal using the ADF4351: IF_TG = 0.56–1.23 GHz

This fits the HMC220 IF port (DC–4 GHz).

The MCU computes IF_TG from the analyzer sweep voltage and harmonic‑mode equations, then programs the ADF4351 accordingly.

---

## Mixer output and TG coherence

The HMC220 mixer produces: RF_TG = LO_2 – IF_TG

Substituting the ranges:

- LO_2 = 8.94–10.28 GHz  
- IF_TG = 0.56–1.23 GHz  

We obtain:  RF_TG = 9.5–11.5 GHz

This exactly matches the analyzer’s displayed frequency.

---

## Module architecture and building blocks

### Analyzer LO doubler
- Input: LO_SA = 4.47–5.14 GHz  
- Output: LO_2 = 8.94–10.28 GHz  
- Purpose: shift analyzer LO into HMC220 LO range while maintaining sweep coherence

### ADF4351 IF_TG generator
- Output: IF_TG = 0.56–1.23 GHz  
- MCU‑controlled and sweep‑synchronous  
- Purpose: provide the IF offset needed to reconstruct RF_TG

### HMC220 mixer
- LO port: 8.94–10.28 GHz  
- IF port: 0.56–1.23 GHz  
- RF port: 9.5–11.5 GHz  
- Purpose: perform the upconversion that produces the 3 cm TG output

### Band‑pass filter (8–12 GHz)
- Removes LO_2 leakage, IF_TG leakage, and mixer images  
- Ensures only the 9.5–11.5 GHz band reaches the amplifier

### RF gain stage + output pad
- Provides ~0 dBm output  
- Maintains linearity across the sweep  
- Ensures stable 50 Ω output at the SMA connector

---

## Performance targets

### Frequency performance
- Output band: 9.5–11.5 GHz  
- Must track analyzer sweep exactly  
- Fast settling to follow analyzer sweep speed

### Amplitude performance
- Target output: ~0 dBm  
- Flatness corrected at system level  
- No compression across sweep

### Spectral purity
- Low LO_2 leakage  
- Low IF_TG leakage  
- Spurs dominated by ADF4351 + multiplier chain  
- Phase noise dominated by analyzer LO

### Implementation constraints
- RF layout suitable for >10 GHz  
- Short traces, via fences, controlled impedance  
- Isolation between LO_2, IF_TG, and RF paths  
- Stable operation across temperature and supply variations
