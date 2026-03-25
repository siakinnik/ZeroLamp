#include "matrix.h"
#include "wlan.h"
#include "bluetooth.h"
#include "program_controller.h"

#include <FastLED.h>
#include <esp_sleep.h>

#define TOUCH_BUTTON_PIN 7  // (TTP223)

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

void setup() {
  Serial.begin(115200);
  delay(200);

  pinMode(TOUCH_BUTTON_PIN, INPUT);

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
  // Button
  if (digitalRead(TOUCH_BUTTON_PIN) == HIGH) {
    delay(50);
    if (digitalRead(TOUCH_BUTTON_PIN) == HIGH) {
      delay(500);
      go_to_sleep();
    }
  }

  bluetooth_tick();
  wlan_tick();
  program_controller_tick();
  random16_add_entropy(random(0x10000));
}
