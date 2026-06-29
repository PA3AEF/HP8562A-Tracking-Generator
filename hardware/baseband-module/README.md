# Base‑Band Tracking Generator Module  
**(0–2.9 GHz fundamental‑mode section)**

The Base‑Band module generates the 0–2.9 GHz portion of the Tracking Generator output.  
It uses the analyzer’s 1st LO as the swept RF input and mixes it with a locally generated LO_TG to recreate the analyzer’s RF sweep at the TG output.

This module contains the **core RF building blocks** for fundamental‑mode operation:

- clean LO_TG generation  
- LO driver amplification  
- fundamental mixer  
- post‑mix filtering  
- output leveling  

All signals remain coherent with the analyzer because the MAX2870 locks to the analyzer’s 10 MHz reference.

---

## Module Overview

The Base‑Band module consists of the following RF chain:

1. **Analyzer 1st LO input from the LO Distribution module**  
2. **MAX2870 PLL generating LO_TG (fixed 3.9107 GHz)**  
3. **LO driver amplifier (20 dB gain)**  
4. **LO band‑pass filter + pad**  
5. **Fundamental mixer (HMC219)**  
6. **Low‑pass filter (DC–3 GHz)**  
7. **Output pad (level trim)**

Each block is described below.

---

## Building Blocks (LO_TG path)

### MAX2870 PLL / LO_TG Source
- Generates the fixed LO_TG required for fundamental mixing.  
- Locked to the analyzer’s 10 MHz reference for coherence.  
- Output level is low (programmable -4 dBm to +5 dBm) and requires external amplification.  
- Ready‑made MAX2870 modules with SPI and SMA connectors work well

---

### LO Driver Amplifier (3.9 GHz)
- Raises the MAX2870 output to proper mixer‑drive levels.  
- Provides stable gain and low added phase noise.  
- Offers isolation between the PLL and the mixer LO port.  
- A boxed 20 dB gain module with SMA I/O is ideal.

---

### LO Band‑Pass Filter (3.9107 GHz) + Pad
- Cleans up PLL and amplifier spurs.  
- Ensures a spectrally clean LO_TG at the mixer.  
- Final pad sets the LO level to ~13 dBm at the HMC219 LO pin.  
- Ready‑made BPF modules with SMA I/O work well, but DIY can perform equally well

---

## Mixer and Output Path

### Fundamental Mixer (HMC219)
- Core element of the Base‑Band module.  
- RF port: analyzer 1st LO (3.9–6.8 GHz)  
- LO port: LO_TG (~13 dBm)  
- IF/RF output: 0–2.9 GHz TG signal  
- Requires good grounding and shielding to minimize LO feedthrough.  
- Ready‑made boxed modules very much simplify construction.

---

### Low‑Pass Filter (DC–3 GHz)
- Removes mixer images and LO leakage.  
- Defines the usable Base‑Band TG output range.  
- Should have low insertion loss and strong stop‑band rejection.  
- DIY CNC‑boxed LPF is fine; ready‑made modules also work.
- Optional pad trims the output to 0 dBm.


**HFSS modeling results optimized for standard LC values:**
![Low Pass FIlter with Fc 3 GHz](/hardware/baseband-module/lpf-3GHz.png)

---

## Performance Goals

### Frequency Tracking
- Output range: 0–2.9 GHz  
- Must follow analyzer sweep exactly  
- Settling must match analyzer sweep speed

### Amplitude Performance
- Target output: ~0 dBm  
- Flatness corrected at system level  
- Avoid compression in the LO driver and mixer

### Spectral Cleanliness
- Low LO leakage  
- Low mixer images  
- Spurs dominated by PLL  
- Phase noise dominated by analyzer LO

### Implementation Notes
- RF‑clean routing up to 3 GHz  
- Strong isolation between LO_TG and RF paths  

---

## Summary

The Base‑Band module is straightforward once broken into functional blocks.  
Each block (PLL, LO driver, mixer, filters, pads) can be built and tested independently.
Many blocks are ready-made available.

---