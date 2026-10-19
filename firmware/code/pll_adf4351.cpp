#include <Arduino.h>
#include <SPI.h>
#include "pll_adf4351.h"
#include "bands.h"

// Internal register cache (per band)
static uint32_t adf4351_regs[6];

// --------------------------------------------------------
// Low-level SPI write
// --------------------------------------------------------
static void adf4351_writeReg(const BandHw& hw, uint32_t value)
{
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    digitalWrite(hw.csPin, LOW);

    SPI.transfer((value >> 24) & 0xFF);
    SPI.transfer((value >> 16) & 0xFF);
    SPI.transfer((value >> 8)  & 0xFF);
    SPI.transfer((value >> 0)  & 0xFF);

    digitalWrite(hw.csPin, HIGH);

    SPI.endTransaction();
    delayMicroseconds(10);   // ADF4351 needs CS high time
}

void adf4351_disable(const BandHw& hw) {
    // Disable RF outputs
    uint32_t r4_off = hw.r4_template & ~( (1 << 5) | (3 << 3) );
    adf4351_writeReg(hw, r4_off);

    // CE low = full shutdown
    digitalWrite(hw.cePin, LOW);
}

// --------------------------------------------------------
// Compute registers (clean, stable, 64-bit safe)
// --------------------------------------------------------
void adf4351_computeRegs(const BandHw& hw, uint64_t f_lo_hz)
{
    const uint32_t F_REF = hw.f_ref_hz;
    const uint32_t R     = hw.r_divider;
    const uint32_t F_PFD = F_REF / R;

    // Divider selection
    uint8_t divSel = 0;
    uint32_t div   = 1;
    while ((f_lo_hz * div) < 2200000000ULL) {
        div <<= 1;
        divSel++;
    }

    uint64_t f_vco = f_lo_hz * div;

    uint32_t INT  = f_vco / F_PFD;
    uint32_t rem  = f_vco % F_PFD;
    uint32_t FRAC = (rem * hw.mod) / F_PFD;

    // R0 and R1 are dynamic for ADF4351
    adf4351_regs[0] = (INT << 15) | (FRAC << 3);
    adf4351_regs[1] = (hw.mod << 3) | 1;

    // R2–R5 from band struct
    adf4351_regs[2] = hw.r2_static;
    adf4351_regs[3] = hw.r3_static;

    // R4 = template + divider
    adf4351_regs[4] = hw.r4_template | (divSel << 20);

    adf4351_regs[5] = hw.r5_static;
}

// --------------------------------------------------------
// Initialization (safe, minimal, stable)
// --------------------------------------------------------
void adf4351_init(const BandHw& hw)
{
    pinMode(hw.csPin, OUTPUT);
    pinMode(hw.cePin, OUTPUT);
    pinMode(hw.ldPin, INPUT);

    digitalWrite(hw.csPin, HIGH);
    digitalWrite(hw.cePin, HIGH);

    // Safe startup frequency
    adf4351_computeRegs(hw, 100000000ULL);

    // Disable RFOUT initially
    uint32_t r4_disabled = adf4351_regs[4] & ~((1 << 5) | (1 << 3));

    // Program R5 → R0 once
    adf4351_writeReg(hw, adf4351_regs[5]);
    adf4351_writeReg(hw, r4_disabled);
    adf4351_writeReg(hw, adf4351_regs[3]);
    adf4351_writeReg(hw, adf4351_regs[2]);
    adf4351_writeReg(hw, adf4351_regs[1]);
    adf4351_writeReg(hw, adf4351_regs[0]);

    adf4351_regs[4] = r4_disabled;
}

// --------------------------------------------------------
// Set frequency (compute + write)
// --------------------------------------------------------
void adf4351_setFrequency(const BandHw& hw, uint64_t f_lo_hz)
{
    adf4351_computeRegs(hw, f_lo_hz);

    // Write R5 → R0
    for (int i = 5; i >= 0; --i)
        adf4351_writeReg(hw, adf4351_regs[i]);
}

// --------------------------------------------------------
// Dump registers
// --------------------------------------------------------
void adf4351_dumpRegs(const BandHw& hw)
{
    Serial.println(F("ADF4351 Register Dump:"));
    for (int i = 5; i >= 0; --i) {
        Serial.print("R");
        Serial.print(i);
        Serial.print(": 0x");
        Serial.println(adf4351_regs[i], HEX);
    }
}

// --------------------------------------------------------
// Lock detect
// --------------------------------------------------------
bool adf4351_isLocked(const BandHw& hw)
{
    return digitalRead(hw.ldPin);
}
