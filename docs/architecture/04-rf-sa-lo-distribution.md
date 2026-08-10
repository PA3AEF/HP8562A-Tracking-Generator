# RF SA‑LO Distribution Module  
**Function:** Conditioning and distribution of the analyzer’s 1st LO  
**Input:** SA 1st LO (3.9–6.8 GHz, ~+16.5 dBm)  
**Outputs:** Four LO feeds to TG modules  
**Target Output Level:** +16 dBm per port (→ +13 dBm at mixer LO pins)

---

## Overview

The RF SA‑LO Distribution module receives the analyzer’s 1st LO and provides a clean, isolated, level‑controlled LO feed to all Tracking Generator modules.

Its responsibilities:

- Protect the analyzer LO port  
- Provide stable impedance and isolation  
- Amplify the LO to compensate for splitter loss  
- Split the LO into four well‑behaved outputs  
- Ensure each module can achieve **+13 dBm at the mixer LO pin**

This board forms the **central LO backbone** for the entire TG system.

---

## Frequency & level plan

### Input  
- SA 1st LO: 3.9–6.8 GHz  
- Typical level: +16.5 dBm  
- Sweep‑synchronous with analyzer RF

### Internal processing  
- Isolator stabilizes return loss and protects the analyzer (a 10dB gain-block would also give enough isolation) 
- Broadband amplifier restores headroom before splitting (probably not necessary with CMOS siwtch such as PE42540)
- Splitter (Wilkinson, relays or MMICs) provides isolation between TG modules  
- Per‑branch pads flatten response and set final level

### Output targets  
Each TG module receives:

- **LO OUT:** +16 dBm nominal  
- After on‑module pad/filter (~3 dB):  
  → **+13 dBm at mixer LO pin**

---

## Block diagram

![SA LO distribution architecture](/docs/architecture/images/sa-lo-distribution.png)

---

## Power budget (nominal)

| Stage | Gain/Loss | Level |
|:-------|-----------:|------:|
| SA 1st LO | — | +16.5 dBm |
| Isolator | –0.5 dB | +16 dBm |
| 4-way split (PE42540) | -1.5 dB | +14.5 dBm |
| TG module LO input | — | +14.5 dBm |
| On‑module pad/filter | –3 dB | **+11 dBm at mixer LO pin** |

---

## Output ports

Four identical LO outputs:

- Base‑Band module  
- 6 cm module  
- 3 cm module  
- 12 mm module  

Each port includes:

- Isolation thru splitter  
- Per‑branch pad  
- 50 ohm matched SMA  
- +16 dBm nominal output

---

## Mechanical / layout notes

- Isolator close to TG input  
- Amplifier and splitter routes short and shielded  
- Clear labeling for all LO outputs  

---

## Future expansion

Designed to support:

- Additional TG modules  
- Higher‑frequency LO distribution  
- Optional per‑branch filtering  
- LO mute switching thru MCU

---