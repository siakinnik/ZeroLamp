#ifndef ZB_MATRIX_H
#define ZB_MATRIX_H

#include <FastLED.h>
#include "build_options.h" // siakinnik - added

// siakinnik - moved to build_options
// #define CURRENT_LIMIT 2000 // maximum current in milliamps
// #define NUM_LEDS 256 // 16x16 matrix
// #define DATA_PIN 5 // GPIO pin connected to WS2812B matrix
// #define SNAKE_MATRIX true
// // #define ROW_MATRIX true

// const int MATRIX_WIDTH = 16;
// const int MATRIX_HEIGHT = 16;

const int MATRIX_BRIGHTNES = 16; // siakinnik - added

void matrix_init();
void matrix_setLedColor(int y, int x, CRGB color);
void matrix_clearLed(int y, int x);

#endif