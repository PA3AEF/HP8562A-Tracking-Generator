# 3 cm Tracking Generator Module (9.5–11.5 GHz)

The 3 cm module is the **harmonic‑mode RF upconversion stage** of the Tracking Generator.  
It reconstructs the analyzer’s **9.5–11.5 GHz** sweep by combining:

- the analyzer’s **1st LO** (derived from the displayed frequency),  
- the analyzer’s **3.1 MHz IF** (used in harmonic mode),  
- a TG‑generated **IF\_TG** from an ADF4351, and  
- a **doubled analyzer LO** to satisfy the HMC220 mixer constraints.

This module is fully coherent with the analyzer because **all TG frequencies ultimately derive from the analyzer’s 1st LO and 10 MHz reference**.

---

## 1. Harmonic‑mode coherence (why this module works)

In the 3 cm band, the HP 8562A/B uses **3× harmonic mixing** with an internal IF of:

**IF\_SA = 3.1 MHz**

The analyzer’s 1st LO therefore follows:

\[
3 \cdot LO_{SA} = RF_{SA} + 3.1\text{ MHz}
\]

For the analyzer’s 3 cm RF band:

- **RF\_SA = 9.5–11.5 GHz**

The corresponding analyzer 1st LO is:

\[
LO_{SA} = \frac{RF_{SA} + 3.1\text{ MHz}}{3}
\]

Which evaluates to:

**LO\_SA = 4.47–5.14 GHz**

This is the *actual* LO range the 3 cm TG module must track.

---

## 2. Why the LO must be doubled

The HMC220 mixer requires:

- **IF port:** DC–4 GHz  
- **LO/RF ports:** 5–12 GHz  

But the analyzer’s 1st LO (4.47–5.14 GHz) is **too low** for the HMC220 LO port.

Therefore the TG uses a **×2 multiplier**:

\[
LO_{2} = 2 \cdot LO_{SA}
\]

Yielding:

**LO₂ = 8.94–10.28 GHz**

This fits perfectly into the HMC220 LO port.

---

## 3. IF\_TG generation (ADF4351)

To complete the upconversion, the TG generates a low‑GHz IF signal:

**IF\_TG = 0.56–1.23 GHz**

This fits the HMC220 IF port (DC–4 GHz).

The MCU computes IF\_TG from the analyzer sweep voltage and harmonic‑mode equations, then programs the ADF4351 accordingly.

---

## 4. Mixer output and TG coherence

The HMC220 produces:

\[
RF_{TG} = LO_{2} - IF_{TG}
\]

Substituting the ranges:

- LO₂ = 8.94–10.28 GHz  
- IF\_TG = 0.56–1.23 GHz  

We obtain:

**RF\_TG = 9.5–11.5 GHz**

This exactly matches the analyzer’s displayed frequency.

---

## 5. Module architecture and building blocks

### **1. Analyzer LO doubler**
- Input: LO\_SA = 4.47–5.14 GHz  
- Output: LO₂ = 8.94–10.28 GHz  
- Purpose:
  - Shift analyzer LO into HMC220 LO range  
  - Maintain sweep coherence  
  - Provide correct LO drive level  

---

### **2. ADF4351 IF\_TG generator**
- Output: **0.56–1.23 GHz**  
- MCU‑controlled, sweep‑synchronous  
- Purpose:
  - Provide the IF offset needed to reconstruct RF\_TG  
  - Stay within HMC220 IF port limits  
  - Maintain fine frequency resolution and fast tuning  

---

### **3. HMC220 mixer**
- LO port: **8.94–10.28 GHz**  
- IF port: **0.56–1.23 GHz**  
- RF port: **9.5–11.5 GHz**  
- Purpose:
  - Perform the actual upconversion  
  - Maintain correct tracking of analyzer sweep  
  - Provide clean sum/difference products  

---

### **4. Band‑pass filter (8–12 GHz)**
- Removes:
  - LO₂ leakage  
  - IF\_TG leakage  
  - Mixer images  
- Ensures only the 9.5–11.5 GHz band reaches the amplifier  

---

### **5. RF gain stage + output pad**
- Provides required output level (~0 dBm)  
- Maintains linearity across the sweep  
- Pads ensure good match and stable output impedance  
- SMA connector provides front‑panel RF output  

---

## 6. Performance targets

### **Frequency performance**
- Output band: **9.5–11.5 GHz**  
- Must track analyzer sweep exactly  
- No discontinuities at band edges  
- Fast settling to follow analyzer sweep speed  

### **Amplitude performance**
- Target output: **≈ 0 dBm**  
- Flatness: system‑level calibration will correct residual slope  
- No compression across sweep  

### **Spectral purity**
- LO₂ leakage: low  
- IF\_TG leakage: low  
- Spurs: dominated by ADF4351 + multiplier chain  
- Phase noise: dominated by analyzer LO  

### **Implementation constraints**
- RF layout suitable for >10 GHz  
- Short traces, via fences, controlled impedance  
- Isolation between LO₂, IF\_TG, and RF paths  
- Stable operation across temperature and supply variations  

---

If you want, I can now:

- regenerate the **Base‑Band hardware README** in the same style  
- update the **LO‑architecture document** with the new harmonic‑mode introduction  
- generate a **block diagram** for the 3 cm module  

Just tell me which one you want next.