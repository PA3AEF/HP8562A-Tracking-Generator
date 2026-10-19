#include <Arduino.h>
#include "pll_control.h"
#include "bands.h"

// Include pll drivers
#include "pll_max2870.h"  // MAX2870 code
#include "pll_adf4351.h"  // ADF4351 code

// --------------------------------------------------------
// Unified PLL initialization
// --------------------------------------------------------
void pll_init(Band band) {
  const BandHw& hw = bands[(uint8_t)band];

  if (hw.pllType == PllType::MAX2870) {
    max2870_init(hw);
    Serial.println("max2870 init");
  } else {
    adf4351_init(hw);
    Serial.println("adf4351 init");
  }
}

// --------------------------------------------------------
// Unified PLL frequency programming
// --------------------------------------------------------
void pll_setFrequency(Band band, uint64_t f_lo_hz) {
  const BandHw& hw = bands[(uint8_t)band];

  if (hw.pllType == PllType::MAX2870)
    max2870_setFrequency(hw, f_lo_hz);
  else
    adf4351_setFrequency(hw, f_lo_hz);
}

// --------------------------------------------------------
// Unified dispatcher to disable PLLs
// --------------------------------------------------------
void pll_disable(const BandHw& hw) {
  if (hw.pllType == PllType::MAX2870) {
    max2870_disable(hw);
    Serial.println("max2870 disable");
  } else {
    adf4351_disable(hw);
    Serial.println("adf4351 disable");
  }
}
// --------------------------------------------------------
// Unified PLL register dump
// --------------------------------------------------------
void pll_dump(Band band) {
  const BandHw& hw = bands[(uint8_t)band];

  if (hw.pllType == PllType::MAX2870)
    max2870_dumpRegs(hw);
  else
    adf4351_dumpRegs(hw);
}

// --------------------------------------------------------
// Unified lock detect
// --------------------------------------------------------
bool pll_isLocked(Band band) {
  const BandHw& hw = bands[(uint8_t)band];

  if (hw.pllType == PllType::MAX2870) {
    Serial.println("max2870 init");
    return max2870_isLocked(hw);
  } else {
    Serial.println("adf4351 locked");
    return adf4351_isLocked(hw);
  }
}
