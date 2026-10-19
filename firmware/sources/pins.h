
#ifndef PINS_H
#define PINS_H

// =========================================================
// SPI0 (hardware)
// =========================================================
constexpr int PIN_SCK  = 18;   // PIN 24 - SPI0 SCK
constexpr int PIN_MOSI = 19;   // PIN 25 - SPI0 MOSI
constexpr int PIN_MISO = 16;   // PIN 21 - SPI0 MISO (not used)

// =========================================================
// Ramp input (ADC0)
// =========================================================
constexpr int PIN_RAMP_ADC = 26;   // PIN 31 - ADC0

// =========================================================
// Rotary switch (Gray code)
// =========================================================
constexpr int PIN_ROT_A = 14;   // PIN 19
constexpr int PIN_ROT_B = 15;   // PIN 20

// =========================================================
// PE42540 LO switch (2-bit select)
// =========================================================
constexpr int PIN_PE_A = 20;    // PIN 26
constexpr int PIN_PE_B = 17;    // PIN 22

// =========================================================
// PE42540 LO switch (2-bit select)
// =========================================================
constexpr int PIN_REF_PRESENT = 21;   // PIN 27
constexpr int PIN_REF_PRESENT_N = 22; // PIN 29

// =========================================================
// Per band control pins
// Each band has: CS, CE, LD, RF_EN
// =========================================================

// ---- BANDBASE ----
constexpr int CS_BASE     = 27;  // PIN 32
constexpr int CE_BASE     = 28;  // PIN 34
constexpr int LD_BASE     = 0;  // PIN 1
constexpr int RFEN_BASE   = 1;  // PIN 2

// ---- 3 cm ----
constexpr int CS_3CM      = 6;  // PIN 9 
constexpr int CE_3CM      = 7;  // PIN 10
constexpr int LD_3CM      = 8;  // PIN 11
constexpr int RFEN_3CM    = 9;  // PIN 12

// ---- 6 cm ----
constexpr int CS_6CM      = 2;   // PIN 4
constexpr int CE_6CM      = 3;   // PIN 5
constexpr int LD_6CM      = 4;   // PIN 6
constexpr int RFEN_6CM    = 5;   // PIN 7

// ---- 15 mm ----
constexpr int CS_12MM     = 10;   // PIN 14
constexpr int CE_12MM     = 11;   // PIN 15
constexpr int LD_12MM     = 12;   // PIN 16
constexpr int RFEN_12MM   = 13;   // PIN 17

#endif