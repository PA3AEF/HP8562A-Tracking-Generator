# 10 MHz Reference Fan‑Out

The 10 MHz reference distribution network provides a stable, low‑noise signal to multiple subsystems within the control module.  
This revision replaces the earlier op‑amp‑based buffer with a **broadband MMIC amplifier** to achieve higher gain, better impedance control, and improved RF integrity.

---

## Design Intent
The goal is to replicate a single precision 10 MHz reference into several identical outputs while maintaining:

- Consistent amplitude and phase across all outputs  
- True 50 Ω system compatibility  
- Minimal additive noise and distortion  
- Simple, robust implementation suitable for RF PCB layout  

---

## Functional Architecture

The circuit can be viewed as **four functional blocks**:

1. **Input Conditioning**  
   - The incoming 10 MHz reference is terminated and AC‑coupled into a broadband amplifier.  
   - The interface maintains 50 Ω impedance to prevent reflections and loading of the source.  
   - A small detection network monitors the presence of the reference signal and converts it into a DC logic level for indication.

2. **Amplification**  
   - A single MMIC amplifier provides sufficient gain to overcome splitter losses.  
   - The device operates linearly at 10 MHz, ensuring clean reproduction of the reference signal.  
   - Power‑supply filtering and decoupling maintain low noise and prevent modulation of the reference.

3. **Signal Distribution**  
   - The amplifier output feeds a passive multi‑way splitter.  
   - Each branch is impedance‑matched and AC‑coupled to its output connector.  
   - The topology ensures isolation between outputs and preserves amplitude balance.

4. **Reference‑Presence Indicator**  
   - A detector monitors the RF level at the amplifier output and generates a logic signal when the 10 MHz reference is present.  
   - This logic drives a **dual‑color LED** that provides immediate visual feedback:  
     - **Red** indicates that the module is powered but no reference signal is detected.  
     - **Green** indicates that the 10 MHz reference is active and within expected amplitude.  
   - The indicator circuit uses a simple envelope‑detection and transistor‑switching scheme to translate the RF presence into a DC control signal.

---

## Operational Behavior

When power is applied, the indicator initially lights **red**, confirming that the module is energized but awaiting a valid reference.  
As soon as the 10 MHz signal reaches nominal amplitude, the detector transitions to **green**, signaling that the reference is locked and distributed correctly.  
If the reference disappears or drops below threshold, the circuit automatically reverts to red, providing a clear visual cue of signal loss.

---

## Performance Characteristics
- **Gain Margin:** The amplifier compensates for splitter attenuation, maintaining nominal output levels.  
- **Isolation:** Passive resistive topology provides adequate separation between outputs for reference use.  
- **Noise Contribution:** The MMIC adds negligible phase noise compared to the master reference.  
- **Bandwidth:** The design remains stable and flat well beyond 10 MHz, ensuring predictable behavior.  
- **Power Supply:** Operates from a single low‑voltage rail with standard RF decoupling practices.

---

## Implementation Notes
- Short RF paths and continuous ground planes.  
- Via fencing around the amplifier region for stability.  
- Decoupling capacitors close to the device pins.  
- Maintain symmetry in the splitter layout to ensure equal path lengths.  
- AC‑couple all outputs to DC-protect downstream circuits.

---

## Summary
This MMIC‑based fan‑out architecture provides a clean, broadband, and impedance‑controlled distribution of the 10 MHz reference.  
It simplifies the design compared to op‑amp buffers, improves gain margin, and ensures reliable operation across all connected modules.

---
