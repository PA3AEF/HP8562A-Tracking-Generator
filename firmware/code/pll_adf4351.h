#ifndef PLL_ADF4351_H
#define PLL_ADF4351_H

#include <stdint.h>
#include "bands.h"

// ADF4351 driver API

void adf4351_init(const BandHw& hw);
void adf4351_setFrequency(const BandHw& hw, uint64_t f_lo_hz);
void adf4351_dumpRegs(const BandHw& hw);
bool adf4351_isLocked(const BandHw& hw);
void adf4351_disable(const BandHw& hw);

#endif

