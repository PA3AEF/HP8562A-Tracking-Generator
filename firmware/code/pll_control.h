#ifndef PLL_CONTROL_H
#define PLL_CONTROL_H

#include <stdint.h>
#include "bands.h"

// Unified PLL control API

void pll_init(Band band);
void pll_setFrequency(Band band, uint64_t f_lo_hz);
void pll_dump(Band band);
bool pll_isLocked(Band band);
void pll_disable(const BandHw& hw);

#endif
