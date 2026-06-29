# 10 MHz Reference Fan‑Out

This document explains the design choices behind the 10 MHz reference distribution amplifier used in this project. The goal is to take a single 10 MHz reference input and generate four clean, isolated, 50 ohm outputs suitable for PLLs, synthesizers, or test equipment.

---

## Overview

The circuit consists of:

- A 50 ohm terminated AC‑coupled input  
- A shared bias node (Vref ≈ 2.5 V)  
- Four unity‑gain OPA1604 (or alike) buffer stages  
- AC‑coupled 50 ohm series‑terminated outputs  

Each output is electrically isolated from the others and presents a proper 50 ohm source impedance.

---

## Why the OPA1604 series?

The OPA1604 is a low‑noise, wide‑bandwidth audio op‑amp that performs exceptionally well at 10 MHz in unity‑gain operation. Although designed for high‑fidelity audio, its combination of bandwidth, linearity, and low noise makes it an excellent choice for the 10 MHz reference‑signal fan‑out.

### Key reasons for choosing it:
- **Unity‑gain bandwidth around 20 MHz**
Provides ample margin for clean, low‑distortion 10 MHz sine‑wave buffering.

- **Low input noise (~4.5 nV/√Hz)**  
Ensures the distribution amplifier does not raise the overall phase‑noise floor.

- **Excellent linearity on a single +5 V supply**
The device remains stable and distortion‑free across the full 10 MHz swing.

- **Quad package**
Four matched channels in one IC simplifies layout and ensurs consistent channel‑to‑channel behavior.

- **High output drive capability**
Easily drives a 50 ohm load through a ~50 ohm series resistor, providing proper source impedance for PLL reference inputs.

### Drop‑in alternatives:
The following quad op‑amps offer similar or improved performance and can be used as direct replacements:

- OPA1644: JFET input, similar bandwidth and noise
- OPA1654: lower noise, higher bandwidth, modern rail‑to‑rail architecture
- OPA1679: low‑power, low‑noise, wide‑bandwidth option

All three devices are suitable for 10 MHz reference fan‑out applications.

---

## AC Bandwidth

The OPA1604 has a unity‑gain bandwidth of approximately 20 MHz.  
In unity gain, the effective –3 dB bandwidth is roughly 10–20 MHz depending on loading.

Since the reference frequency is 10 MHz, the amplifier operates well within its linear region.  
Amplitude error and phase shift are negligible for this application.

---

## Noise Performance

The output noise is dominated by:

- Op‑amp voltage noise (~4.5 nV/√Hz)  
- Thermal noise of the 50 ohm input and output resistors (~0.9 nV/√Hz each)

Combined noise density at the output is approximately:`~4.7 nV/√Hz`

Integrated over a 100 kHz bandwidth:`~1.5 µV RMS`

For a 1 Vpp (0.35 V RMS) reference signal, this corresponds to:`~107 dB SNR`

This is far below the phase‑noise floor of typical PLLs or signal analyzers, ensuring the fan‑out stage does not degrade system performance.

---

## Channel Isolation

Each output buffer has:

- Its own op‑amp channel  
- A 100 ohm series resistor at the non‑inverting input  
- A ~50 ohm series resistor at the output  
- Independent AC‑coupling

This provides excellent isolation between channels.

Expected crosstalk at 10 MHz: –60 to –80 dB, which is more than enough for reference distribution.

---

## Why AC‑Coupling and Vref Biasing?

The OPA1604 cannot handle input signals near 0 V when powered from a single +5 V rail.  
To operate linearly, the input must be biased to mid‑supply.

The design uses:

- AC‑coupling capacitor at the input  
- A 2.5 V virtual ground (R5/R6/C5)  
- All op‑amp non‑inverting inputs tied to this node

This ensures:

- The 10 MHz signal sits at the center of the op‑amp’s linear range  
- No DC from the source propagates into the buffers  
- All channels share the same stable bias point

---

## Output Stage

Each output uses:

` Op‑amp OUT → AC‑coupling capacitor → ~50 ohm series → SMA`

This provides:

- Correct 50 ohm source impedance  
- DC isolation  
- Protection against load variations or reflections  
- Clean, predictable behavior with any 50 ohm RF input

---

## Summary

The combination of:

- OPA1604 quad op‑amp  
- AC‑coupled, biased input  
- Four unity‑gain buffers  
- Proper 50 ohm input and output matching  

results in a **low‑noise, high‑isolation, wide‑bandwidth 10 MHz reference fan‑out** suitable for demanding RF and timing applications.

---