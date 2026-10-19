#include <Arduino.h>
#include "pe42540.h"
#include "pins.h"

void initPeSwitch() {
  pinMode(PIN_PE_A, OUTPUT);
  pinMode(PIN_PE_B, OUTPUT);
  digitalWrite(PIN_PE_A, HIGH);
  digitalWrite(PIN_PE_B, HIGH);
}

void setPeForBand(Band band) {
  uint8_t code = bands[(uint8_t)band].peCode;

  int pinMap[4][2] = {
    {LOW, LOW},    // RF1 - code = 0 (Base Band)
    {LOW, HIGH},   // RF2 - code = 1
    {HIGH, LOW},   // RF3 - code = 2
    {HIGH, HIGH}   // RF4 - code = 3 
  };
  
  Serial.print("setPeForBand. . . ");
  Serial.println(code);

  digitalWrite(PIN_PE_A, pinMap[code][0]);
  digitalWrite(PIN_PE_B, pinMap[code][1]);
}
