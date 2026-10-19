#include "bands.h"
#include "pins.h"
#include <Arduino.h>

Band currentBand = Band::BANDBASE;  // default startup band

void enableBand(Band b) {
  currentBand = b;

  // Disable all RF power domains
  digitalWrite(RFEN_BASE, LOW);
  digitalWrite(RFEN_3CM, LOW);
  digitalWrite(RFEN_6CM, LOW);
  digitalWrite(RFEN_12MM, LOW);

  // Enable selected band
  const BandHw& hw = bands[(uint8_t)currentBand];
  digitalWrite(hw.rfenPin, HIGH);

  Serial.print("Band selected: ");
  Serial.println(BandText[(uint8_t)currentBand]);
  Serial.println(" ");
}

// --------------------------------------------------------
// Hardware configuration for each band
// --------------------------------------------------------
//
// Tune values per band as needed.
// They match the existing TG hardware layout.
// --------------------------------------------------------
const BandHw bands[(uint8_t)Band::BAND_COUNT] = {

  // ----------------------------------------------------
  // BANDBASE  (MAX2870, fixed 3.9107 GHz,10 MHz ref)
  // ----------------------------------------------------
  {
    PllType::MAX2870,
    CS_BASE,
    CE_BASE,
    LD_BASE,
    RFEN_BASE,

    10000000UL,  // f_ref = 10 MHz
    1,           // r_devider = 1
    100,         // MOD = 100
    false,       // feedbackDiv2 (unused for MAX2870)
    0,           // PE switch code

    FreqMode::FIXED,
    3910700000ULL,  // f_fixed
    0, 0,           // f_start/f_stop unused

    // Known-good baseband config:
    0x20000321,  // R1
    0x18005E42,  // R2
    0x0000000B,  // R3
    0x608C8024,  // R4 (PWR=0; computeRegs will OR-in divider if needed)
                 // PWR RFOUTA Bits [3:4] 24 -> -4 dBm, 2C -> -1 dBm, 34 -> +2 dBm, 3C -> +5 dBm
    0x00400005   // R5
  },

  // ----------------------------------------------------
  // BAND6CM  (ADF4351, fixed 310.7 MHz, 10 MHz ref)
  // ----------------------------------------------------
  {
    PllType::ADF4351,
    CS_6CM,
    CE_6CM,
    LD_6CM,
    RFEN_6CM,

    10000000UL,  // f_ref = 10 MHz
    1,           // r_devider = 1
    100,         // MOD = 100
    false,       // feedbackDiv2 (unused)
    1,           // PE switch code

    FreqMode::FIXED,
    310700000ULL,  // f_fixed = 310.7 MHz
    0, 0,          // sweep unused

    // Static ADF4351 registers
    0x20000321,  // R1 (MOD=100, PHASE=1)
    0x00005E42,  // R2 (CP=5 mA, PD polarity=1, etc.)
    0x0000000B,  // R3 (clock div disabled, CSR off)
    0x608C8034,  // R4 (OUTDIV = devide by 8, RFOUT enabled low power, RFAUX disabled)
                 // PWR RFOUTA Bits [3:4] 24 -> -4 dBm, 2C -> -1 dBm, 34 -> +2 dBm, 3C -> +5 dBm
    0x00400005   // R5 (LD digital, control bits)
  },

  // ----------------------------------------------------
  // BAND3CM  (ADF4351, fixed 310.7 MHz, 10 MHz ref)
  // ----------------------------------------------------
  {
    PllType::ADF4351,
    CS_3CM,
    CE_3CM,
    LD_3CM,
    RFEN_3CM,

    10000000UL,  // f_ref = 10 MHz
    1,           // r_devider = 1
    100,         // MOD = 100
    false,       // feedbackDiv2 (unused)
    2,           // PE switch code

    FreqMode::FIXED,
    310700000ULL,  // f_fixed = 310.7 MHz
    0, 0,          // sweep unused

    // Static ADF4351 registers
    0x20000321,  // R1 (MOD=100, PHASE=1)
    0x00005E42,  // R2 (CP=5 mA, PD polarity=1, etc.)
    0x0000000B,  // R3 (clock div disabled, CSR off)
    0x608C8034,  // R4 (OUTDIV = devide by 8, RFOUT enabled, low power, RFAUXOUT disabled)
                 // PWR RFOUTA Bits [3:4] 24 -> -4 dBm, 2C -> -1 dBm, 34 -> +2 dBm, 3C -> +5 dBm
    0x00400005   // R5 (LD digital, control bits)
  },


  // ----------------------------------------------------
  // BAND12MM  (ADF4351, sweep?)  *** TODO ***
  // ----------------------------------------------------
  {
    PllType::ADF4351,
    CS_12MM,
    CE_12MM,
    LD_12MM,
    RFEN_12MM,

    10000000UL,  // f_ref = 10 MHz
    1,           // r_devider = 1
    100,         // MOD = 100
    false,       // feedbackDiv2 (unused)
    3,           // PE switch code



    FreqMode::SWEEP,
    0,
    18000000000ULL,  // f_start (TODO)
    20000000000ULL,  // f_stop  (TODO)


    // Static ADF4351 config for 12MM band (*** TODO *** Copy from 3 cm. Needs adjust probably)
    0x20000321,  // R1 (MOD=100, PHASE=1)
    0x00005E42,  // R2 (CP=5 mA, PD polarity=1, etc.)
    0x0000000B,  // R3 (clock div disabled, CSR off)
    0x608C8034,  // R4 (OUTDIV = devide by 8, RFOUT enabled, low power, RFAUXOUT disabled)
                 // PWR RFOUTA Bits [3:4] 24 -> -4 dBm, 2C -> -1 dBm, 34 -> +2 dBm, 3C -> +5 dBm
    0x00400005   // R5 (LD digital, control bits)

  }
};
