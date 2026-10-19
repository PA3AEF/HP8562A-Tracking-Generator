#ifndef BANDS_H
#define BANDS_H

#include <stdint.h>

// --------------------------------------------------------
// Band enumeration
// --------------------------------------------------------
enum class Band : uint8_t {
    BANDBASE = 0,
    BAND6CM  = 1,
    BAND3CM  = 2,
    BAND12MM = 3,
    BAND_COUNT
};

static const char *BandText[] = { "Base Band", "6 cm", "3 cm", "12 mm" };

void enableBand(Band b);


// --------------------------------------------------------
// PLL type
// --------------------------------------------------------
enum class PllType : uint8_t {
    MAX2870,
    ADF4351
};

// --------------------------------------------------------
// Hardware mapping
// --------------------------------------------------------
enum class FreqMode : uint8_t {
    FIXED,
    SWEEP
};

struct BandHw {
    PllType pllType;

    uint8_t csPin;
    uint8_t cePin;
    uint8_t ldPin;
    uint8_t rfenPin;

    uint32_t f_ref_hz;
    uint32_t r_divider;
    uint32_t mod;
    bool     feedbackDiv2;
    uint8_t  peCode;

    FreqMode mode;
    uint64_t f_fixed;
    uint64_t f_start;
    uint64_t f_stop;

    uint32_t r1_static;
    uint32_t r2_static;
    uint32_t r3_static;
    uint32_t r4_template;   // divider bits cleared
    uint32_t r5_static;

};


// --------------------------------------------------------
// Global band table
// --------------------------------------------------------
extern const BandHw bands[(uint8_t)Band::BAND_COUNT];


// --------------------------------------------------------
// Global current band
// --------------------------------------------------------
extern Band currentBand;

#endif
