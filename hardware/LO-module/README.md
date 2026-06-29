# LO Module — External 1st LO Distribution

The LO Module takes the **1st LO output from the HP 8562A/B Spectrum Analyzer** and distributes it cleanly and at controlled power levels to all TG RF bands.  
The module provides isolation, gain compensation, RF switching, and MCU‑based band selection.

---

## Purpose

- Accept the **external 1st LO** (3.9–6.8 GHz, ~16.5 dBm) from the HP8562A/B  
- Provide **3.5–7 GHz isolation** to protect the analyzer and stabilize the LO feed  
- Apply **~10 dB broadband gain** to compensate for PE42540 switch losses  
- Route the LO to **four isolated SMA outputs**  
- Allow **MCU‑controlled band selection** via PE4250/PE42540 RF switches  
- Deliver **~+16 dBm** per‑port LO drive for mixers in each TG band module

---

## Block Diagram

![TG system architecture](/hardware/LO-module/lo-module.png)

---

## LO Signal Path

### 1. 1st LO Input
- Source: HP 8562A/B Spectrum Analyzer  
- Frequency: **3.9–6.8 GHz**  
- Power: **~16.5 dBm**  
- Input is routed directly into the isolator to protect the analyzer and stabilize impedance.

### 2. Isolator (3.5–7 GHz)
- Ensures reverse isolation  
- Prevents reflections from the TG system  
- Provides a stable load to the analyzer’s LO output

### 3. Broadband Amplifier (~10 dB)
- Frequency range: **3.9–6.8 GHz**  
- Purpose: compensate insertion loss of PE42540 switch  
- Ensures final per‑port LO level remains at **~+16 dBm**

### 4. PE42540 4‑Way RF Switch/Splitter
- Provides **four isolated LO outputs**  
- MCU‑controlled switching  
- Low insertion loss, but compensated by the broadband amp  
- Output level per port: **~+16 dBm**

### 5. SMA Outputs
- One SMA per band module  
- Clean, isolated LO feed  
- Stable drive level for mixers

### 6. MCU Control (Raspberry Pi Pico)
- Controls PE4250/PE42540  
- Selects active LO output path  
- Provides band‑select logic for TG modules

---

## Design Notes

- LO drive target: **~+16 dBm** at each SMA  
- Isolator ensures analyzer protection and stable LO impedance  
- Broadband amp compensates switch losses and maintains output power  
- PE42540 chosen for isolation and MCU‑controlled routing  
- Maintain short RF traces and controlled impedance routing



---

