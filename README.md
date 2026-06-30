# Tracking Generator for the HP 8562A/B Spectrum Analyzer  
**Reconstructing the Analyzer’s RF Sweep from Its Local Oscillator**
**A modular, analyzer‑synchronous architecture**

---

## What this project is

The HP 8562A/B spectrum analyzer does not include a tracking generator.  
However, it exposes enough of its internal LO system to build one externally.

This project implements a **modular, sweep‑synchronous Tracking Generator (TG)** that behaves as if it were a native part of the HP 8562A/B.  
It reconstructs the analyzer’s RF sweep using only:

- 1st LO Output (about 3.9–6.8 GHz)  
- LO Sweep Output (0–10 V, 0.5 V/GHz)  
- 10 MHz reference

The TG becomes a slave to the analyzer’s LO system and rebuilds the RF sweep in real time across multiple microwave bands.

---

## Why build a Tracking Generator for the HP 8562A/B?

The HP 8562A/B is a legendary instrument: fast, sensitive, and extremely stable.  
But without a tracking generator, it cannot perform:

- filter alignment  
- cavity tuning  
- antenna measurements  
- scalar network analysis  
- frequency response characterization  

This project fills that gap with a TG that follows the analyzer sweep exactly, using the analyzer’s own LO architecture.

---

## How the analyzer sweeps — and how the TG reconstructs the RF

The HP 8562A/B does not sweep an RF source.  
It sweeps its **first local oscillator** and mixes incoming signals down to a fixed IF.  
To cover 1 kHz–26 GHz, it uses **automatic harmonic mixing**, where each RF band uses a different harmonic of the LO:

| RF Band | Harmonic n | IF | LO Formula |
|--------:|:----------:|----------:|-----------|
| 1 kHz–2.9 GHz | 1 | 3.9107 GHz | LO_SA = RF_SA + 3.9107 GHz |
| 2.75–6.46 GHz | 1 | 310.7 MHz | LO_SA = RF_SA + 0.3107 GHz |
| 5.86–13.0 GHz | 2 | 310.7 MHz | LO_SA = (RF_SA + 0.3107 GHz) / 2 |
| 12.4–19.7 GHz | 3 | 310.7 MHz | LO_SA = (RF_SA + 0.3107 GHz) / 3 |
| 19.1–26.0 GHz | 4 | 310.7 MHz | LO_SA = (RF_SA + 0.3107 GHz) / 4 |

For each band, the analyzer follows: `n * LO_SA = RF_SA + IF`

Because **n changes with band**, the analyzer LO becomes **non‑linear** with respect to the displayed frequency.

A tracking generator must compensate for this non‑linearity to stay aligned.

---

## How the TG reconstructs the analyzer RF

The TG uses the analyzer LO_SA (or a harmonic of it) as the primary LO and subtracts a fixed IF to recreate the analyzer’s RF:

```
RF_TG = (n * LO_SA) – IF_TG
```

Where:

- IF_TG = 310.7 MHz (fixed for all microwave TG modules)  
- n = analyzer harmonic mode for that band  

This yields:

- Base‑Band (n = 1):  
  RF_TG = LO_SA – 3.9107 GHz

- 6 cm (n = 1):  
  RF_TG = LO_SA – 0.3107 GHz

- 3 cm (n = 2):  
  RF_TG = (2 × LO_SA) – 0.3107 GHz

- 12 mm (n = 4, concept):  
  RF_TG = (4 × LO_SA) – 0.3107 GHz

This architecture reqires **no swept PLLs** in the microwave TG modules.  
Sweep coherence comes entirely from the analyzer LO.

---

## High‑level TG architecture

The TG system is composed of modular RF boards:

- **MCU board:**  
  Reads sweep voltage, computes RF_SA for calibration, programs PLLs

- **RF SA‑LO Distribution board:**  
  Conditions and splits the analyzer’s 1st LO to all TG modules

- **Base‑Band TG module:**  
  0–2.9 GHz (uses MAX2870)

- **6 cm TG module:**  
  4.4–6.4 GHz (LO_SA direct, IF_TG = 310.7 MHz)

- **3 cm TG module:**  
  9.5–11.5 GHz (LO_SA ×2, IF_TG = 310.7 MHz)

- **12 mm TG module (concept):**  
  22–26 GHz (LO_SA ×4, IF_TG = 310.7 MHz)

Conceptually:

```
Analyzer → LO Distribution → TG Modules → RF Outputs
Analyzer → 10 MHz → PLLs
Analyzer → V_sweep → MCU → Harmonic modules
```

Each TG module reconstructs the analyzer RF at its own band using a mixer‑based architecture.

---

## TG coverage limits

- **Implemented TG bands:**  
  - Base‑Band (0–2.9 GHz)  
  - 6 cm (4.4–6.4 GHz)  
  - 3 cm (9.5–11.5 GHz)

- **Conceptual / future TG bands:**  
  - 12 mm (22–26 GHz)

- **Analyzer coverage:**  
  - Up to 26 GHz with Option 026  
  - TG coverage currently ends at 11.5 GHz

---

## Repository structure

```
/docs/architecture
    01-tg-system-architecture.md
    02-lo-architecture.md
    03-analyser-lo-internals.md
    04-rf-sa-lo-distribution.md
    05-baseband-module.md
    06-6cm-module.md
    07-3cm-module.md
    08-12mm-module.md
/docs/architecture/images
    architecture diagrams
/firmware
    MCU firmware (Raspberry Pi Pico)
    overview
    images
/hardware/<module>
    schematics, layouts, BOMs, images
/mechanical
    enclosures, front panels
/usage
    calibration and measurement tools
```

---

## Status

- File: [example S21 3 cm lossy filter](./images/s21-3cm-lossy-filter.jpg)
- File: [example S11 3 cm pole filter](./images/s11-3cm-pole-filter.jpg)
- MCU board: concept tested OK, PCB in development  
- LO Distribution: work in progress  
- Base‑Band module: proof of concept tested OK  
- 3 cm module: proof of concept tested OK (tracking at 10 GHz with 2 GHz span)  
- 6 cm module: architecture defined  
- 12 mm module: conceptual design complete  

---

## License

MIT License.  
See `LICENSE` for details.

