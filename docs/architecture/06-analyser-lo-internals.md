# Analyzer LO Internals (3 cm Band)  
**Purpose:** Explain how the HP 8562A/B analyzer generates the 4.47–5.14 GHz 1st LO range used by the Tracking Generator.

---

## Overview

The analyzer’s internal LO chain uses **harmonic generation** and **two IF conversions** to reach the 3 cm band.  
The TG locks onto the analyzer’s synthesizer output (LO_SA), which runs from **4.47–5.14 GHz**.  
This frequency range results from the analyzer’s internal first IF of **3.910 GHz** and its **×3 harmonic LO scheme**.

---

## Internal signal flow

1. **RF_SA (9.5–11.5 GHz)** enters the first mixer.  
2. The analyzer’s **LO synthesizer** (4.47–5.14 GHz) is multiplied ×6 and divided ÷2, producing **3 × LO_synth = 13.4–15.4 GHz**.  
3. The first mixer combines RF_SA and 3 × LO_synth to yield the **first IF = 3.910 GHz**.  
4. A **second LO ≈ 3.6 GHz** down‑converts IF1 to the **final IF = 3.1 MHz**, which feeds the display chain.

---

## Frequency relationships

- First conversion:  IF1 = LO1 – RF_SA  
- With LO1 = 3 × LO_synth and IF1 = 3.910 GHz: **3 × LO_synth = RF_SA + 3.910 GHz**  
- Therefore:  **LO_synth = (RF_SA + 3.910 GHz) / 3**

For RF_SA = 9.5–11.5 GHz:  
- LO_synth_min = (9.5 + 3.910) / 3 = 4.47 GHz  
- LO_synth_max = (11.5 + 3.910) / 3 = 5.14 GHz  

Hence the analyzer’s synthesizer output (LO_SA) runs from **4.47–5.14 GHz**, which is the range distributed to the TG.

---

## Summary table

| Parameter | Symbol | Value / Range | Notes |
|------------|---------|---------------|-------|
| Displayed RF band | RF_SA | 9.5–11.5 GHz | Analyzer 3 cm band |
| First IF | IF1 | 3.910 GHz | Fixed internal IF |
| Synthesizer output | LO_SA | 4.47–5.14 GHz | TG reference |
| Effective 1st LO | LO1 | 13.4–15.4 GHz | 3 × LO_SA |
| Final IF | IF_SA | 3.1 MHz | Display IF |

---

## Integration with TG

The TG uses this measured LO_SA range to maintain coherence:

- Doubled LO:  LO_2 = 2 × LO_SA = 8.94–10.28 GHz  
- IF_TG = LO_2 – RF_SA = 0.56–1.23 GHz  
- Mixer output:  RF_TG = LO_2 – IF_TG = RF_SA  

This ensures perfect frequency tracking between analyzer and TG.

