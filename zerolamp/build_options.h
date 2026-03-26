// siakinnik - added
// --------------------
// Build options
// --------------------

#ifndef BUILD_OPTIONS_H
#define BUILD_OPTIONS_H

#define LEGACY_ZEROLAMP true
// #define ZEROLAMP_S3V1 true

#ifdef ZEROLAMP_S3V1
#define TOUCH_BUTTON_PIN 7  // deep-sleep button (TTP223)
#endif

#define CURRENT_LIMIT 2000  // maximum matrix current in milliamps
#define NUM_LEDS 256        // 16x16 matrix

#ifdef ZEROLAMP_S3V1
#define DATA_PIN 5  // GPIO pin connected to WS2812B matrix
#endif

#ifdef LEGACY_ZEROLAMP
#define DATA_PIN 19  // GPIO pin connected to WS2812B matrix
#endif

#define SNAKE_MATRIX true
// #define ROW_MATRIX true

const int MATRIX_WIDTH = 16;
const int MATRIX_HEIGHT = 16;
#endif