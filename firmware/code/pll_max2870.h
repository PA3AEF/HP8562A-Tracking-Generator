#ifndef PLL_MAX2870_H
#define PLL_MAX2870_H

#include <stdint.h>
#include "bands.h"

// MAX2870 driver API

void max2870_init(const BandHw& hw);
void max2870_setFrequency(const BandHw& hw, uint64_t f_lo_hz);
void max2870_dumpRegs(const BandHw& hw);
bool max2870_isLocked(const BandHw& hw);
void max2870_disable(const BandHw& hw);

#endif

