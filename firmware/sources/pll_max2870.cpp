#include <Arduino.h>
#include <SPI.h>
#include "pll_max2870.h"
#include "bands.h"

// Internal register cache (per band)
static uint32_t max2870_regs[6];

// --------------------------------------------------------
// Low-level SPI write
// --------------------------------------------------------
static void max2870_writeReg(const BandHw& hw, uint32_t value) {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  digitalWrite(hw.csPin, LOW);

  SPI.transfer((value >> 24) & 0xFF);
  SPI.transfer((value >> 16) & 0xFF);
  SPI.transfer((value >> 8) & 0xFF);
  SPI.transfer((value >> 0) & 0xFF);

  digitalWrite(hw.csPin, HIGH);

  SPI.endTransaction();
  delayMicroseconds(10);  // MAX2870 requires CS high time
}


void max2870_disable(const BandHw& hw) {
  // Force LD low: R5[23:22] = 00
  uint32_t r5_ld_low = hw.r5_static & ~(0b11u << 22);
  max2870_writeReg(hw, r5_ld_low);

  digitalWrite(hw.cePin, LOW);
}



// --------------------------------------------------------
// Compute registers (my old working logic)
// --------------------------------------------------------
void max2870_computeRegs(const BandHw& hw, uint64_t f_lo_hz) {
  const uint32_t F_REF = hw.f_ref_hz;
  const uint32_t R = hw.r_divider;
  const uint32_t F_PFD = F_REF / R;

  // Divider selection
  uint8_t divSel = 0;
  uint32_t div = 1;
  while ((f_lo_hz * div) < 3000000000ULL) {
    div <<= 1;
    divSel++;
  }

  uint64_t f_vco = f_lo_hz * div;

  // INT + FRAC
  uint32_t INT = f_vco / F_PFD;
  uint32_t rem = f_vco % F_PFD;
  uint32_t FRAC = (rem * hw.mod) / F_PFD;

  // R0: dynamic
  max2870_regs[0] =
    ((INT & 0xFFFF) << 15) | ((FRAC & 0x0FFF) << 3);

  // R1–R3, R5: static
  max2870_regs[1] = hw.r1_static;
  max2870_regs[2] = hw.r2_static;
  max2870_regs[3] = hw.r3_static;
  max2870_regs[5] = hw.r5_static;

  // R4: template + dynamic divider
  max2870_regs[4] =
    hw.r4_template | ((divSel & 0x7) << 20);
}

// --------------------------------------------------------
// Initialization (safe startup sequence)
// --------------------------------------------------------
void max2870_init(const BandHw& hw) {

  pinMode(hw.csPin, OUTPUT);
  pinMode(hw.cePin, OUTPUT);
  pinMode(hw.ldPin, INPUT);

  digitalWrite(hw.csPin, HIGH);
  digitalWrite(hw.cePin, LOW);  // keep disabled during programming

  // Compute safe startup frequency
  max2870_computeRegs(hw, 100000000ULL);

  // Disable RF output
  uint32_t r4_disabled = max2870_regs[4] & ~((1 << 5) | (3 << 3));


  // Program registers R5 → R0
  max2870_writeReg(hw, max2870_regs[5]);
  max2870_writeReg(hw, r4_disabled);
  max2870_writeReg(hw, max2870_regs[3]);
  max2870_writeReg(hw, max2870_regs[2]);
  max2870_writeReg(hw, max2870_regs[1]);
  max2870_writeReg(hw, max2870_regs[0]);

  // Toggle CE to start VCO calibration
  digitalWrite(hw.cePin, LOW);
  delayMicroseconds(10);
  digitalWrite(hw.cePin, HIGH);


//  digitalWrite(hw.cePin, HIGH);

  // Empirically determined that the MAX2870 requires approx. 10 ms after
  // CE assertion before reliable lock acquisition.
  // Use 50ms to be safe
  delay(50);

  // Allow lock detect (LD mode: 01 = digital lock detect)
  max2870_writeReg(hw, hw.r5_static);

  // Keep RFOUT disabled until frequency is set
  max2870_regs[4] = r4_disabled;
}

// --------------------------------------------------------
// Set frequency (compute + write)
// --------------------------------------------------------
void max2870_setFrequency(const BandHw& hw, uint64_t f_lo_hz) {
  max2870_computeRegs(hw, f_lo_hz);

  // Write R5 → R0
  for (int i = 5; i >= 0; --i)
    max2870_writeReg(hw, max2870_regs[i]);
}

void printHex32(uint32_t value) {
  char buf[9];  // 8 hex chars + null terminator
  for (int i = 7; i >= 0; --i) {
    uint8_t nibble = value & 0xF;
    buf[i] = (nibble < 10) ? ('0' + nibble) : ('A' + (nibble - 10));
    value >>= 4;
  }
  buf[8] = '\0';
  Serial.println(buf);
}


// --------------------------------------------------------
// Dump registers
// --------------------------------------------------------
void max2870_dumpRegs(const BandHw& hw) {
  // Serial.println(F("MAX2870 Register Dump:"));
  for (int i = 0; i <= 5; i++) {
    Serial.print("R");
    Serial.print(i);
    Serial.print(": ");
    printHex32(max2870_regs[i]);
  }
}

// --------------------------------------------------------
// Lock detect
// --------------------------------------------------------
bool max2870_isLocked(const BandHw& hw) {
  return digitalRead(hw.ldPin);
}
