#include "matrix.h"
#include <cassert>

CRGB leds[NUM_LEDS];

void matrix_init() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  // siakinnik - removed
  // FastLED.setBrightness(16);

  FastLED.setBrightness(MATRIX_BRIGHTNES);

  if (CURRENT_LIMIT > 0) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  }

  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.clear(true);
}

#ifdef ROW_MATRIX
inline int ledId(int y, int x) {
  // Added rotation 90°
  int newY = x;
  int newX = MATRIX_WIDTH - 1 - y;
  return newY * MATRIX_WIDTH + newX;
}
#endif

#ifdef SNAKE_MATRIX
inline int ledId(int y, int x) {
  if (x % 2 == 0) {
    // led's numbered from top to bottom
    return MATRIX_HEIGHT * x + y;
  }
  return MATRIX_HEIGHT * x + MATRIX_HEIGHT - 1 - y;  // mirror along the y axis
}
#endif

void matrix_setLedColor(int y, int x, CRGB color) {
  assert(y >= 0);
  assert(y < MATRIX_HEIGHT);
  assert(x >= 0);
  leds[ledId(y, x % MATRIX_WIDTH)] = color;
}

void matrix_clearLed(int y, int x) {
  matrix_setLedColor(y, x, CRGB::Black);
}
