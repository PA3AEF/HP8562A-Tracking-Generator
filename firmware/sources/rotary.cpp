#include <Arduino.h>
#include "rotary.h"
#include "pins.h"

void initRotary() {
  pinMode(PIN_ROT_A, INPUT_PULLUP);
  pinMode(PIN_ROT_B, INPUT_PULLUP);
}

Band readBandFromRotary() {
  bool a = digitalRead(PIN_ROT_A);
  bool b = digitalRead(PIN_ROT_B);

  if (a && b) return Band::BANDBASE;
  if (a && !b) return Band::BAND6CM;
  if (!a && b) return Band::BAND3CM;
  if (!a && !b) return Band::BAND12MM;

  return Band::BANDBASE;
}

// Gray-code band switch debounce. During transitions the switch can briefly present
// valid intermediate Gray states. These could be interpreted as real band changes.
// Two identical readings separated by 20 ms are required before accepting a new band.

Band readStableBand()
{
    Band b1 = readBandFromRotary();

    delay(10);

    Band b2 = readBandFromRotary();

    if (b1 == b2)
        return b1;

    return currentBand;
}
