#include "matrix.h"
#include "wlan.h"
#include "bluetooth.h"
#include "program_controller.h"
#include "build_options.h"  // siakinnik - added

#include <FastLED.h>
#include <esp_sleep.h>

// siakinnik - moved to build_options
// #ifdef ZEROLAMP_S3V1
// #define TOUCH_BUTTON_PIN 7  // deep-sleep button (TTP223)
// #endif

#ifdef ZEROLAMP_S3V1
void go_to_sleep() {
  Serial.println("Going to deep sleep...");

  // Clear matrix
  FastLED.clear(true);
  delay(50);

  // Button wakeup
  esp_sleep_enable_ext0_wakeup(
    (gpio_num_t)TOUCH_BUTTON_PIN,
    1  // HIGH
  );

  Serial.flush();
  esp_deep_sleep_start();
}
#endif

void setup() {
  Serial.begin(115200);
  delay(200);

#ifdef ZEROLAMP_S3V1
  pinMode(TOUCH_BUTTON_PIN, INPUT);
#endif

  Serial.println("Initializing ZeroLamp...");

  unsigned long seed = (analogRead(0) + analogRead(1)) ^ 0xdeadbeef;
  randomSeed(seed);
  random16_set_seed(~seed);

  wlan_init();
  bluetooth_init();
  matrix_init();
  program_controller_init();

  Serial.println("ZeroLamp ready.");
}

void loop() {
#ifdef ZEROLAMP_S3V1
  // Button
  if (digitalRead(TOUCH_BUTTON_PIN) == HIGH) {
    delay(50);
    if (digitalRead(TOUCH_BUTTON_PIN) == HIGH) {
      delay(500);
      go_to_sleep();
    }
  }
#endif

  bluetooth_tick();
  wlan_tick();
  program_controller_tick();
  random16_add_entropy(random(0x10000));
}
