#include <Arduino.h>
#include "ramp.h"
#include "pins.h"

uint64_t computeLo(const BandHw& hw) {

    if (hw.mode == FreqMode::FIXED) {
        return hw.f_fixed;
    }

    // SWEEP mode
    int adc = analogRead(PIN_RAMP_ADC);
    float t = adc / 1023.0f;

    return hw.f_start + (uint64_t)((hw.f_stop - hw.f_start) * t);
}

