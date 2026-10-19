// Raspberry Pi PICO controls the Tracking Generator's mixed‑PLL synthesizer system (MAX2870. ADF4351, etc.), 
// band‑switching logic, and RF routing. It is designed for clarity, reproducibility, and modularity, 
// following a clean separation between hardware abstraction and signal‑chain logic.
//
// PA3AEF Oct 2026
//

#include <Arduino.h>
#include <SPI.h>

#include "pins.h"
#include "bands.h"
#include "rotary.h"
#include "ramp.h"
#include "pe42540.h"
#include "pll_control.h"

// #define DEBUG 1

void setup() {
  Serial.begin(115200);
  SPI.begin();

  delay(100);

  // RF Circuitry
  pinMode(RFEN_BASE, OUTPUT);
  pinMode(RFEN_3CM, OUTPUT);
  pinMode(RFEN_6CM, OUTPUT);
  pinMode(RFEN_12MM, OUTPUT);

  // Safe startup: all RF circuitry off
  digitalWrite(RFEN_BASE, LOW);
  digitalWrite(RFEN_3CM, LOW);
  digitalWrite(RFEN_6CM, LOW);
  digitalWrite(RFEN_12MM, LOW);

  initRotary();
  initPeSwitch();

  delay(100);
  currentBand = readBandFromRotary();

  Serial.print("Startup band = ");
  Serial.println((int)currentBand);

  setPeForBand(currentBand);

  pll_init(currentBand);

  uint64_t f_lo = computeLo(bands[static_cast<uint8_t>(currentBand)]);

  pll_setFrequency(currentBand, f_lo);

  // Fire up RF circuitry
  enableBand(currentBand);
}

void loop() {

  static Band lastBand = currentBand;

  // --- 1. Read rotary band selector ---
  Band newBand = readStableBand();

  // --- 2. Band changed? Then disable old PLL and switch ---
  if (newBand != lastBand) {
    // Disable previous PLL
    pll_disable(bands[static_cast<uint8_t>(lastBand)]);

    // Switch band
    currentBand = newBand;
    lastBand = newBand;

    // Compute LO for new band
    uint64_t f_lo = computeLo(bands[static_cast<uint8_t>(newBand)]);

    // Init + program new PLL
    pll_init(newBand);
    pll_setFrequency(newBand, f_lo);

    // Switch over LO input
    setPeForBand(newBand);

    // Enable RF circuitry
    enableBand(newBand);
  }

  // --- 3. Normal operation: update LO for current band ---
  //uint64_t f_lo = computeLo(bands[static_cast<uint8_t>(currentBand)]);
  uint64_t f_lo;

#ifdef DEBUG
  if (Serial.available()) {
    // --- 4. Handle <CR> for debug dump ---
    int c = Serial.read();
    if (c == '\r' || c == '\n') {
      pll_dump(currentBand);

      bool a = digitalRead(PIN_ROT_A);
      bool b = digitalRead(PIN_ROT_B);

      Serial.print("Rotary: ");
      Serial.print(a);
      Serial.println(b);
      bool locked;
      locked = pll_isLocked(currentBand);
      Serial.println(locked ? "Locked? YES" : "Locked? NO");
      Serial.println("Step done. Press <CR> for next.");
    }
  }
#endif

}
